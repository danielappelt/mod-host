/*
  Copyright 2007-2012 David Robillard <http://drobilla.net>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <lilv/lilv.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <jack/ringbuffer.h>

#include "mod-semaphore.h"
#include "zix/thread.h"

typedef struct WORKER_T {
    jack_ringbuffer_t * requests;
    jack_ringbuffer_t * responses;
    void *response;
    sem_t sem;
    ZixThread thread;
    const LV2_Worker_Interface *iface;
    LilvInstance *instance;
    bool exit;
} worker_t;


void worker_init(worker_t *worker, LilvInstance *instance, const LV2_Worker_Interface *iface, uint32_t size);
void worker_finish(worker_t *worker);
LV2_Worker_Status worker_schedule(LV2_Worker_Schedule_Handle handle, uint32_t size, const void *data);
void worker_emit_responses(worker_t *worker);
