#undef PD

#if defined(PD_PASS1)

#include <stdio.h>
#include <stdlib.h>

#  define PD(label) label##Element,

   enum ERR_CODES {SUCCESS, FAILURE, NO_DATA};

   enum ELEMENT_VALS {UnknownElement = -1,
#else
#  define PD_PASS1
#  include "storage.h"
#  undef PD_PASS1
#  if defined(ENUM_ONLY)
#    define PD(label)
#  else
#    define PD(label) {#label, label##Element},
#  endif

#if !defined(ENUM_ONLY)

struct _elementLookup {
  char *elementName;
  enum ELEMENT_VALS elementVal;
} elementLookup[] = {

#endif
#endif

#include "parserdefs.h"

#if defined(PD_PASS1)
 NUM_ITEMS};

#else
#  if !defined(ENUM_ONLY)
  {NULL}};

#  endif
int            initElementLookup(void);
enum ELEMENT_VALS lookupElement(const char *elementName);
enum ERR_CODES storeElementData(enum ELEMENT_VALS type, char *elementText);
int            getElementCount(enum ELEMENT_VALS type);
char          *getElementData(enum ELEMENT_VALS type);
char          *lookupElementName(enum ELEMENT_VALS type);
void           dumpStorage(enum ELEMENT_VALS type);
char          *getElementName(enum ELEMENT_VALS type);

#define stringize(x)  #x


#endif

#undef PD



