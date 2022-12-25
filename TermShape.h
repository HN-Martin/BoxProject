#ifndef  TERM__SHAPE_H
#define  TERM__SHAPE_H

#include "Shape.h"


namespace Netlist{
	class TermShape : public Shape {
		public :
		enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };

		TermShape ( Symbol *, std::string name , int x , int y , std::string align);

		~ TermShape ();

		Box getBoundingBox () const ;

		inline Term * getTerm () const { return term_;}

		inline int getX () const { return x_;}

		inline int getY () const { return y_;}

		void toXml (std::ostream &);

		static TermShape * fromXml ( Symbol * owner, xmlTextReaderPtr);

		std::string alignString() const;

		private :
		Term * term_ ;
		int x_ , y_ ;
	    NameAlign align_;
	};
}

#endif  // TERM__SHAPE_H
