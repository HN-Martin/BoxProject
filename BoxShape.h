#include "Box.h"
#include "Shape.h"
#include <iostream>

namespace Netlist{

	class BoxShape : public Shape{
	private:
		Box	 box_;

	  public:
		BoxShape	(Symbol* , const Box&);

		BoxShape ( Symbol *,  int, int, int , int );

		~BoxShape	();

		Box 		getBoundingBox () const;
	
		void	toXml (std::ostream&);

		static BoxShape* fromXml( Cell* , xmlTextReaderPtr );
	
	};
}

