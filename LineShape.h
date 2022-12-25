
#include "Box.h"
#include "Shape.h"

namespace Netlist{
	class LineShape : public Shape{
		public :
		LineShape ( Symbol *, int x1 , int y1 , int x2 , int y2 );

		~ LineShape ();

		Box getBoundingBox () const ;

		void toXml (std::ostream&);

		LineShape* fromXml( Cell* , xmlTextReaderPtr );

		private :
		Symbol * owner_ ;
		int x1_ , y1_ , x2_ , y2_ ;
	};
}
