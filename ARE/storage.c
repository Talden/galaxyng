#include <string.h>

#include "storage.h"

#define DEBUG            0
#define INBUF_SIZE    8192
#define ELEMENT_CODE_LEN   16
#define forever          1
/*====================================================================*/
/*            FUNCTION:  elementComp                                     */
/*--------------------------------------------------------------------*/

static int elementComp (const void *element1, const void *element2) {
	return strcmp (((struct _elementLookup *) element1)->elementName,
				   ((struct _elementLookup *) element2)->elementName);
}

/*====================================================================*/
/*            FUNCTION:  initElementLookup                               */
/*--------------------------------------------------------------------*/

int initElementLookup () {
	static int initialized = 0;
	
	int tags;
	int elements;
	
	if (!initialized) {
		initialized = 1;
		qsort ((char *) elementLookup, NUM_ELEMENTS,
			   sizeof (struct _elementLookup), elementComp);
    }
	
	return NUM_ELEMENTS;
}

/*====================================================================*/
/*            FUNCTION:  lookupElement                                   */
/*--------------------------------------------------------------------*/
enum ELEMENT_VALS lookupElement (const char *elementName) {
	struct _elementLookup srchElement;
	struct _elementLookup *dataElement;

	srchElement.elementName = strlwr(strdup (elementName));

/*  fprintf(stderr, "Looking up TAG--->%s\n", elementName);  */

	dataElement = (struct element *) bsearch ((void *) &srchElement, (void *)
											  elementLookup,
											  NUM_ELEMENTS,
											  sizeof (srchElement),
											  elementComp);

	free (srchElement.elementName);
	
	if (dataElement)
		return dataElement->elementVal;
	else
		return UNKNOWN_ELEMENT;
}

/*====================================================================*/
/*            FUNCTION: storeElementData                                 */
/*--------------------------------------------------------------------*/
enum ERR_CODES storeElementData (enum ELEMENT_VALS type, char *elementText) {
	int elementTextLen;              /* how much do we have to store? */
	int tagIdx;                   /* shortcut to the member element */
	int requiredTextSize;         /* how big do we make it? */

#if DEBUG == 1
	fprintf (stderr, "Came into STOREELEMENTDATA with ELEMENTTEXT-->%s\n",
			 elementText);
#endif
	
	if (elementText == NULL)
		return NO_DATA;
	
	if ((elementTextLen = strlen (elementText)) == 0)
		return NO_DATA;

	return SUCCESS;
}
/*====================================================================*/
/*            FUNCTION:  getElementCount                                 */
/*--------------------------------------------------------------------*/

int getElementCount (enum ELEMENT_VALS type) {
	return bibDoc.tag[type].count;
}

/*====================================================================*/
/*            FUNCTION:  getElementData                                  */
/*--------------------------------------------------------------------*/
char* getElementData (enum ELEMENT_VALS type) {
	int i;

	return "";
}

/*====================================================================*/
/*            FUNCTION:   lookupElementName                              */
/*--------------------------------------------------------------------*/
char * lookupElementName (enum ELEMENT_VALS type) {
	int loopVar;

	for (loopVar = 0; loopVar < NUM_ELEMENTS; loopVar++)
		if (elementLookup[loopVar].elementVal == type)
			return elementLookup[loopVar].elementName;

	return "No Name Found";
}

y/*====================================================================*/
/*            FUNCTION: dumpStorage                                   */
/*--------------------------------------------------------------------*/
void dumpStorage (enum ELEMENT_VALS type) {
	int i;
	
	return;
}

/*====================================================================*/
/*            FUNCTION:  getElementName                                  */
/*--------------------------------------------------------------------*/
char* getElementName (enum ELEMENT_VALS type) {
	int i;

	for (i = 0; i < MAX_DOC_ELEMENTS; i++) {
		if (elementLookup[i].elementVal == type) {
			return elementLookup[i].elementName;
        }
    }
	return "UnknownElement";
}
