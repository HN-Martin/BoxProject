#ifndef  NETLIST_INST_H
#define  NETLIST_INST_H


#include <string>
#include "Indentation.h"
#include  "XmlUtil.h"

namespace Netlist {

  class Term;
  class Net;
  class Instance{
  public:
  static       Instance*           fromXml       ( Cell* , xmlTextReaderPtr );
                                   Instance      ( Cell* owner, Cell* model, const std::string& );
                                   ~Instance     ();
  
         const std::string&        getName       () const;
               Cell*               getMasterCell () const;
               Cell*               getCell       () const;
         const std::vector<Term*>& getTerms      () const;
               Term*               getTerm       ( const std::string& ) const;
               Point               getPosition   () const;
               bool                connect       ( const std::string& name, Net* );
               void                add           ( Term* );
               void                remove        ( Term* );
               void                setPosition   ( const Point& );
               void                setPosition   ( int x, int y );
               void                toXml         ( std::ostream& ) const;
  private:
  Cell*               owner_;
  Cell*               masterCell_;
  std::string         name_;
  std::vector<Term*>  terms_;
  Point               position_;
  };

  class Cell;
}

#endif  // NETLIST_INST_H
