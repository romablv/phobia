/*
   Phobia Motor Controller for RC and robotics.
   Copyright (C) 2015 Roman Belov <romblv@gmail.com>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "lib.h"
#include "sh.h"
#include "tel.h"

tel_t				tel;

void tel_capture()
{
	int			j, tail;

	for (j = 0; j < tel.p_size; ++j)
		tel.s_average[j] += tel.p_list[j];

	tel.s_clock++;

	if (tel.s_clock >= tel.s_clock_scale) {

		tel.clock = 0;

		for (j = 0; j < tel.p_size; ++j) {

			*tel.pZ++ = tel.s_average[j] / tel.s_clock_scale;
			tel.s_average[j] = 0;
		}

		tail = tel.pZ - tel.pD + tel.p_size;
		tel.enabled = (tail < TELSZ) ? tel.enabled : 0;
	}
}

void tel_show()
{
	short int		*pZ;
	int			j;

	pZ = tel.pD;

	while (pZ < tel.pZ) {

		for (j = 0; j < tel.p_size; ++j)
			printf("%i ", *pZ++);

		puts(EOL);
	}
}
