#include "Point.h"
#include "Symbol.h"
#include "TermShape.h"
#include "LineShape.h"
#include "TermShape.h"
#include "Indentation.h"
#include <vector>


namespace Netlist{
		using namespace std;
	     	 Symbol::Symbol          ( Cell* c):owner_(c){
	     		 c->setSymbol(*this);
	     	 }

             Symbol::~Symbol          (){}

             Cell*                      Symbol::getCell         () const{ return owner_;}

             Box                        Symbol::getBoundingBox  () const{
            	 Box b;
            	 vector<Shape *>::const_iterator is=shapes_.begin();

            	 for(;is != shapes_.end();++is)
            		 b.merge((*is)->getBoundingBox());

            	 return b;
             }

             Point                      Symbol::getTermPosition ( Term* t) const{
            	 	return t->getNode()->getPosition();
             }

             TermShape*                 Symbol::getTermShape    ( Term* t) const{
            	 Point p= getTermPosition(t);

            	 for( size_t i=0; i<shapes_.size();i++){
            		 const TermShape* ts = dynamic_cast<const TermShape*>(shapes_[i]);
            		 if(ts && (ts->getX()==p.getX()) && (p.getY()==ts->getY())) return ts;
            	 }

            	 return NULL;
             }
      
             void                       Symbol::add             ( Shape* s){
            	 shapes_.push_back(s);
             }

             void                       Symbol::remove          ( Shape* s){
            	 vector<Shape *>::iterator is=shapes_.begin();

            	 for(;is != shapes_.end();++is)
            		 if((*is)==s)
            			 shapes_.erase(is);
             }

             void                       Symbol::toXml           ( std::ostream& os) const{
            	 os << "<symbol>";
            	 ++ indent;
            	 vector<Shape *>::iterator is=shapes_.begin();

            	 for(;is != shapes_.end();++is)
            		 (*is)->toXml(os);
            	 -- indent;
            	 os << "</symbol>" << endl;
             }

             static Symbol*             Symbol::fromXml         ( Cell* c, xmlTextReaderPtr reader){
            	 	 Symbol *s=new Symbol(c);
            	 	 string type;

            	 	 while (true){
            	 		int status = xmlTextReaderRead(reader);
            	 		if (status != 1) {
            	 		  if (status != 0) {
            	 		          cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << endl;
            	 		  }
            	 		  goto end;
            	 		}
            	 		type=xmlCharToString(xmlTextReaderConstLocalName( reader ));

            	 		switch(type){
							case "line" : s->add(LineShape::fromXml(s,reader)); break;
							case "term" : s->add(TermShape::fromXml(s,reader));break;
							case "box"  : s->add(BoxShape::fromXml(s,reader));break;
							case "ellipse" : break;
							case "arc"   : break;
							default	: goto end;
             	 		}
            	 	 }
            	 	 end: return s;
             }
}
