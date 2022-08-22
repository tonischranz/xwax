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
#include <stdlib.h>

#include "cues.h"
#include "debug.h"

void cues_reset(struct cues *q)
{
    size_t n;

    for (n = 0; n < MAX_CUES; n++)
        q->position[n] = CUE_UNSET;
}

/*
 * Unset the given cue point
 */

void cues_unset(struct cues *q, unsigned int label)
{
    debug("clearing cue point %d", label);
    q->position[label] = CUE_UNSET;
}

void cues_set(struct cues *q, unsigned int label, double position)
{
    debug("setting cue point %d to %0.2f", label, position);
    assert(label < MAX_CUES);
    q->position[label] = position;
}

double cues_get(const struct cues *q, unsigned int label)
{
    assert(label < MAX_CUES);
    return q->position[label];
}

/*
 * Return: the previous cue point before the current position, or CUE_UNSET
 */

double cues_prev(const struct cues *q, double current)
{
    size_t n;
    double r;

    r = CUE_UNSET;

    for (n = 0; n < MAX_CUES; n++) {
        double p;

        p = q->position[n];
        if (p == CUE_UNSET)
            continue;

        if (p > r && p < current)
            r = p;
    }

    return r;
}

/*
 * Return: the next cue point after the given position, or CUE_UNSET
 */

double cues_next(const struct cues *q, double current)
{
    size_t n;
    double r;

    r = CUE_UNSET;

    for (n = 0; n < MAX_CUES; n++) {
        double p;

        p = q->position[n];
        if (p == CUE_UNSET)
            continue;

        if (p < r && p > current)
            r = p;
    }

    return r;
}
