 /*
  * cve_main.h
  *
  * Copyright (C) 2013 - Rocaloid Development Group (RDG)
  *
  * Created by rgwan 
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  */
 #ifndef CVE_MAIN_H
 #define CVE_MAIN_H
// Command Argument List

static const char *optString = "d:o:hv?";

static const struct option longOpts[] = 
{
    { "datadir", required_argument, NULL, 'd' },
    { "output", required_argument, NULL, 'o' },
    { "help", no_argument, NULL, 'h' },
	{ "verbose", no_argument, NULL, 'v' },
    { NULL, no_argument, NULL, 0 }
};

 
 #endif /*NIAM_EVC _H */
 