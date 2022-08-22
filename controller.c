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

#include <assert.h>

#include "controller.h"
#include "deck.h"
#include "debug.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

int controller_init(struct controller *c, struct controller_ops *ops,
                    void *local, struct rt *rt)
{
    debug("%p", c);

    c->fault = false;
    c->ops = ops;
    c->local = local;

    return rt_add_controller(rt, c);
}

void controller_clear(struct controller *c)
{
    debug("%p", c);
    c->ops->clear(c);
}

/*
 * Add a deck to this controller, if possible
 */

void controller_add_deck(struct controller *c, struct deck *d)
{
    debug("%p adding deck %p", c, d);

    if (c->ops->add_deck(c, d) == 0) {
        debug("deck was added");

        assert(d->ncontrol < ARRAY_SIZE(d->control)); /* FIXME: report error */
        d->control[d->ncontrol++] = c; /* for callbacks */
    }
}

/*
 * Get file descriptors which should be polled for this controller
 *
 * Important on systems where only callback-based audio devices
 * (eg. JACK) are used. We need to return some descriptors so
 * that the realtime thread runs.
 *
 * Return: the number of pollfd filled, or -1 on error
 */

ssize_t controller_pollfds(struct controller *c, struct pollfd *pe, size_t z)
{
    if (c->ops->pollfds != NULL)
        return c->ops->pollfds(c, pe, z);
    else
        return 0;
}

void controller_handle(struct controller *c)
{
    if (c->fault)
        return;

    if (c->ops->realtime(c) != 0) {
        c->fault = true;
        fputs("Error handling hardware controller; disabling it\n", stderr);
    }
}
