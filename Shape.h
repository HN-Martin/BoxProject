#include "XmlUtil.h"
#include "Box.h"

namespace Netlist{
	class Cell;
	class Symbol;
	
	class Shape {
		public :
		Shape ( Symbol * );

		virtual ~ Shape ();

		inline Symbol * getSymbol () const { return owner_;}

		inline Cell * getCell () const { return owner_->getCell(); }

		virtual Box getBoundingBox () const = 0;

		virtual void toXml( std::ostream& ) ;

		static Shape* fromXml( Cell* , xmlTextReaderPtr );

		private :
		Symbol * owner_ ;
	};
}
