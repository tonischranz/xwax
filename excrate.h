/*
 * Copyright (C) 2021 Mark Hills <mark@xwax.org>
 *
 * This file is part of "xwax".
 *
 * "xwax" is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License, version 3 as
 * published by the Free Software Foundation.
 *
 * "xwax" is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef EXCRATE_H
#define EXCRATE_H

#include <sys/poll.h>
#include <sys/types.h>

#include "external.h"
#include "list.h"
#include "library.h"
#include "observer.h"

struct excrate {
    struct list excrates;
    unsigned int refcount;
    const char *search;
    struct listing listing, *storage;
    struct event completion;

    /* State of the external scan process */

    struct list rig;
    pid_t pid;
    int fd;
    struct pollfd *pe;
    bool terminated;

    /* State of reader */

    struct rb rb;
};

struct excrate* excrate_acquire_by_scan(const char *script, const char *search,
                                        struct listing *storage);

void excrate_acquire(struct excrate *e);
void excrate_release(struct excrate *e);

/* Used by the rig and main thread */

void excrate_pollfd(struct excrate *tr, struct pollfd *pe);
void excrate_handle(struct excrate *tr);

#endif
