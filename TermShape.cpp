#include "TermShape.h"
#include <iostream>
#include "Indentation.h"

namespace Netlist {

	TermShape :: TermShape ( Symbol * owner , std::string name , int x , int y , std::string align): Shape ( owner ) , term_ ( NULL ), x_ ( x ), y_ ( y ) {
		switch(align){
			case "top_right": align_=1; break;
			case "top_left": align_=2; break;
			case "bottom_left": align_=3; break;
			case "bottom_right": align_=4;
		}
		Cell * cell = getCell ();
		term_ = cell -> getTerm ( name );
	}

	TermShape ::~ TermShape () { }

	Box TermShape :: getBoundingBox () const{
		return Box ( x_ , y_ , x_ , y_ );
	}

	std::string TermShape::alignString () const{
		switch(align_){
			case 1 : return "top_right";
			case 1 : return "top_left";
			case 1 : return "bottom_left";
			case 1 : return "bottom_right";
		}
		std::cerr << "Invalid align type."<< std::endl;
		return NULL;
	}



	void TermShape::toXml (std::ostream & o){
		o << indent << "<term name=\"" << term_->getName() << "\" x=\"" << x_ << "\" y=\"" << y_ ;
		o << "\" align=\"" << alignString() << "\" >"<< std::endl;
	}

	static TermShape * fromXml(Symbol *owner, xmlTextReaderPtr reader){
		TermShape * ts=NULL;

		int x = 0 , y=0;
		std::string name=xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) ),
		align= xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ) );;

		 if (   xmlGetIntAttribute( reader, "x1", x )
			and xmlGetIntAttribute( reader, "y1", y )
		 	 and name
			 and align)
				ts = new TermShape(owner, name, x, y, align);


		return ts;
	}
}
