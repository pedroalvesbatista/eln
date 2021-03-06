// Items/Digraphs.H - This file is part of eln

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

// Digraphs.H

#ifndef DIGRAPHS_H

#define DIGRAPHS_H

#include <QMap>
#include <QString>

class Digraphs {
public:
  static bool anyEndingWith(QString);
  static bool contains(QString);
  static QString map(QString);
private:
  static QMap<QString, QString> const &allEndingWith(QString);
  static QMap<QString, QMap<QString, QString> > const &chars();
};

#endif
