/*
 * Copyright (C) 2012 Mark Hills <mark@pogo.org.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <stdio.h>

#include "status.h"

static void no_notify(void) {}

static const char *current = "";
static void (*notify)(void) = &no_notify;

/*
 * Return: current status string
 */

const char* status(void)
{
    return current;
}

/*
 * Set status to reference a static string
 *
 * Post: reference on s is held
 */

void status_set(const char *s)
{
    current = s;
    notify();
}

/*
 * Set status to a formatted string
 */

void status_printf(const char *t, ...)
{
    static char buf[256];
    va_list l;

    va_start(l, t);
    vsnprintf(buf, sizeof buf, t, l);
    va_end(l);

    current = buf;
}

/*
 * Set a function to call as a notification when status changes
 */

void status_notify(void (*f)(void))
{
    notify = f;
}
