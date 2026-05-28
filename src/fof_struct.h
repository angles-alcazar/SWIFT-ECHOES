/*******************************************************************************
 * This file is part of SWIFT.
 * Copyright (c) 2019 Matthieu Schaller (schaller@strw.leidenuniv.nl)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#ifndef SWIFT_FOF_STRUCT_H
#define SWIFT_FOF_STRUCT_H

/* Config parameters. */
#include <config.h>
#include <stddef.h>

#ifdef WITH_FOF

/**
 * @brief BH-carried fields for the FoF scheme.
 * Used only by ECHOES.
 */
struct fof_galaxy_data {
  /*! Sum of masses of all particles in the galaxy */
  float group_mass;

  /*! Maximum group mass ever reached by the galaxy */
  float max_group_mass;

  /*! boolean flag for whether the BH particle thinks it's a central BH
   * sutherland TODO: Maybe save some spaceby reducing the bit footprint of the
   * bool? For now all the fields are at least 32 bits, so reducing this to 1
   * bit wouldn't save any space, but if we have more flags in the future, we
   * could combine them into a single int, or use C bitfields. What version of C
   * introduced bitfields? If it's too late we might not want to include them so
   * as not to break support for older compilers. Unless we don't really care?
   * Maybe it's better to say we're using a more recent gcc version. */
  int is_central;

  /* How far is the BH to the center of mass of its group?
   * sutherland TODO: How should we handle cases where a BH is no longer in a
   * group? Options (that I see): Set this to 0, set it to FLT_MAX, keep it at
   * its previous value */
  float distance_to_CoM;
};

/**
 * @brief Particle-carried fields for the FoF scheme.
 */
struct fof_gpart_data {

  /*! Particle group ID */
  size_t group_id;

  /*! Size of the FOF group of this particle */
  size_t group_size;
};

#else

/**
 * @brief Particle-carried fields for the FoF scheme.
 */
struct fof_gpart_data {};

/**
 * @brief BH-carried fields for the FoF scheme.
 * Used only by ECHOES.
 */
struct fof_galaxy_data {};

#endif

#endif /* SWIFT_FOF_STRUCT_H */
