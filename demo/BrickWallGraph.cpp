/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#include "Common.h"
#include "BrickWallGraph.h"

BrickWallGraph::BrickWallGraph()
{
	m_szTitle="Gain";
}

double BrickWallGraph::NormToFuncX( double x, bool bInverse )
{
	return NormToFreq( x, bInverse );
}

double BrickWallGraph::NormToFuncY( double y, bool bInverse )
{
	const double ymin=-0.2;
	const double ymax=1.8;

	if( bInverse )
	{
		// [ymin..ymax] -> [0..1]
		return (y-ymin)/(ymax-ymin);
	}
	else
	{
		// [0..1] -> [ymin..ymax]
		return ymin+y*(ymax-ymin);
	}
}

double BrickWallGraph::Func( double x )
{
	Dsp::Complex c=m_filter->Response( 2*Dsp::kPi*x/m_spec->sampleRate );
	double y=std::abs(c);
	return y;
}

void BrickWallGraph::DrawExtras( Graphics &g )
{
	g.setColour( m_cAxis );
	DrawAxisX( g, 1 );
	DrawAxisX( g, 0 );

	DrawCutoff( g );
}