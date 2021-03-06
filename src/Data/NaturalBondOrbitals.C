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

#include "NaturalBondOrbitals.h"
#include <QDebug>


namespace IQmol {
namespace Data {


NaturalBondOrbitals::NaturalBondOrbitals(
   unsigned const nAlpha, 
   unsigned const nBeta, 
   ShellList const& shells, 
   QList<double> const& alphaCoefficients, 
   QList<double> const& alphaEnergies,  
   QList<double> const& betaCoefficients,  
   QList<double> const& betaEnergies,
   QString const& label)
 : Orbitals(Orbitals::NaturalTransition, shells, alphaCoefficients, betaCoefficients, label), 
   m_alphaEnergies(alphaEnergies), m_betaEnergies(betaEnergies),
   m_nAlpha(nAlpha), m_nBeta(nBeta)
{
}


double NaturalBondOrbitals::alphaOrbitalEnergy(unsigned i) const 
{
   return ((int)i < m_alphaEnergies.size()) ? m_alphaEnergies[i] : 0.0;
}


double NaturalBondOrbitals::betaOrbitalEnergy(unsigned i) const 
{
   double energy(0.0);
   if (m_restricted) {
      energy = alphaOrbitalEnergy(i);
   }else if ((int)i < m_betaEnergies.size()) {
      energy = m_betaEnergies[i];
   }
   return energy;
}


bool NaturalBondOrbitals::consistent() const
{
   bool ok(Orbitals::consistent());

   //TODO: remove when NTOs/NBOs properly subclassed.
   if (orbitalType() == Orbitals::NaturalTransition) {
      ok = ok && m_alphaEnergies.size() == (int)m_nOrbitals;
      if (!m_restricted) ok = ok && m_betaEnergies.size() == (int)m_nOrbitals;
   }
      
   return ok; 
}


void NaturalBondOrbitals::dump() const
{
   Orbitals::dump();
}

} } // end namespace IQmol::Data
