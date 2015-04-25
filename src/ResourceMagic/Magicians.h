// ResourceMagic/Magicians.H - This file is part of eln

/* eln is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   eln is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eln.  If not, see <http://www.gnu.org/licenses/>.
*/

// Magicians.H

#ifndef MAGICIANS_H

#define MAGICIANS_H

#include "Magician.h"
#include "Style.h"

class Magicians {
public:
  Magician const *first(QString refText) const;
  Magician const *next(QString refText, Magician const *) const;
  static Magicians const &magicians(Style const &);
private:
  static QMap<Style const *, Magicians *> &stylemap();
  Magicians(Style const &st);
  QList<Magician const *> mm;  
};

#endif