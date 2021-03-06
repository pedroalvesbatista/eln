// Data/TitleData.H - This file is part of eln

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

// TitleData.H

#ifndef TITLEDATA_H

#define TITLEDATA_H

#include "Data.h"
#include <QList>
#include "TextData.h"

class TitleData: public Data {
  Q_OBJECT;
public:
  TitleData(Data *parent=0);
  virtual ~TitleData();
  TextData const *text() const;
  TextData *text();
  bool isDefault() const;
signals:
  void textMod();
protected:
  virtual void loadMore(QVariantMap const &);
};

#endif
