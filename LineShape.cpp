#include "LineShape.h"
#include "Indentation.h"


namespace Netlist{
		LineShape::LineShape ( Symbol *owner, int x1 , int y1 , int x2 , int y2 ): Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2){}

		LineShape::~ LineShape (){}

		Box LineShape::getBoundingBox () const{
			return Box(x1_,y1_,x2_,y2_);
		}

		void LineShape::toXml (std::ostream& o){
			o << indent << "<line x1=\"" << x1_ << "\" y1=\"" << y1_ << "\" x2=\"" << x2_ ;
			o << "\" y2=\"" << y2_ << "\" >"<< std::endl;
		}

		static LineShape* LineShape::fromXml( Symbol *owner, xmlTextReaderPtr reader){
				LineShape * ls=NULL;

				int x1 = 0 , y1=0, x2=0, y2=0;

				        if (   xmlGetIntAttribute( reader, "x1", x1 )
				           and xmlGetIntAttribute( reader, "y1", y1 )
				           and xmlGetIntAttribute( reader, "x2", x2 )
				           and xmlGetIntAttribute( reader, "y1", y2 ))
				        	ls = new LineShape(owner, x1, y1, x2, y2);


				return ls;
		}
}

