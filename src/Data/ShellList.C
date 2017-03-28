/*******************************************************************************
       
  Copyright (C) 2011-2015 Andrew Gilbert
           
  This file is part of IQmol, a free molecular visualization program. See
  <http://iqmol.org> for more details.
       
  IQmol is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option) any later
  version.

  IQmol is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.
      
  You should have received a copy of the GNU General Public License along
  with IQmol.  If not, see <http://www.gnu.org/licenses/>.  
   
********************************************************************************/

#include "ShellList.h"
#include <QDebug>
#include <cmath>


namespace IQmol {
namespace Data {

unsigned ShellList::nBasis() const
{
    unsigned n(0);
    for (int i = 0; i < size(); ++i) {
        n += at(i)->nBasis();
    }
   return n;
}


void ShellList::boundingBox(qglviewer::Vec& min, qglviewer::Vec& max) 
{
   if (isEmpty()) {
      min.x = min.y = min.z = 0.0;
      max.x = max.y = max.z = 0.0;
      return;
   }

   at(0)->boundingBox(min, max);

   qglviewer::Vec tmin, tmax;
   ShellList::const_iterator iter;
   for (iter = begin(); iter != end(); ++iter) {
       (*iter)->boundingBox(tmin, tmax);
       min.x = std::min(tmin.x, min.x);
       min.y = std::min(tmin.y, min.y);
       min.z = std::min(tmin.z, min.z);
       max.x = std::max(tmax.x, max.x);
       max.y = std::max(tmax.y, max.y);
       max.z = std::max(tmax.z, max.z);
   }
}


void ShellList::dump() const
{
   unsigned n(0), s(0), p(0), d5(0), d6(0), f7(0), f10(0), g9(0), g15(0);

   ShellList::const_iterator iter;
   for (iter = begin(); iter != end(); ++iter) {
       switch ((*iter)->angularMomentum()) {
          case  Data::Shell::S:    ++s;    n +=  1;  break;
          case  Data::Shell::P:    ++p;    n +=  3;  break;   
          case  Data::Shell::D5:   ++d5;   n +=  5;  break;
          case  Data::Shell::D6:   ++d6;   n +=  6;  break;   
          case  Data::Shell::F7:   ++f7;   n +=  7;  break;
          case  Data::Shell::F10:  ++f10;  n += 10;  break;   
          case  Data::Shell::G9:   ++g9;   n +=  9;  break;
          case  Data::Shell::G15:  ++g15;  n += 15;  break;   
       }   
   }   

   QString check("OK");
   if (n != nBasis()) check.prepend("NOT ");
   qDebug() << "Basis function check:     " << check;

   QString types("   S    P   D5   D6   F7  F10");
   QString tally = QString("%1 %2 %3 %4 %5 %6").arg( s,4).arg( p,4).arg( d5,4)
                                                  .arg(d6,4).arg(f7,4).arg(f10,4);
   qDebug() << "Shell types:              " << types;
   qDebug() << "                          " << tally;
   
   //List<Shell>::dump();
}

} } // end namespace IQmol::Data