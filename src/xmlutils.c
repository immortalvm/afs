/*****************************************************************************
**
**  Functions for working with XML.
**
**  Creation date:  2017/07/06
**  Created by:     Piql AS
**
**
**  Copyright (c) 2014 Piql AS. All rights reserved.
**
**  This file is part of the afs library
**
*****************************************************************************/

//  PROJECT INCLUDES
//

#include "xmlutils.h"
#include "boxing/string.h"


// PUBLIC AFS XML UTILS FUNCTIONS
//


//----------------------------------------------------------------------------
/*! 
 *  \defgroup utils Utilities
 *  \brief          Various utility functions.
 *  \ingroup afs
 *
 *  Helper functions.
 */


/*! 
  * \addtogroup utils
  * \{
  */


//----------------------------------------------------------------------------
/*!
 *  \brief The function adds text to the XML node.
 *
 *  The function adds text to the XML node.
 *  If string pointer or node pointer is NULL then function return without adding.
 *
 *  \param[out]  text   Text to be added to the node.
 *  \param[in]   node   XML node pointer.
 */

void afs_xmlutils_set_node_text(const char* text, mxml_node_t* node)
{
    if (text == NULL || node == NULL)
    {
        return;
    }

    if (boxing_string_length(text) == 0 && text != NULL)
    {
        mxmlNewOpaque(node, "/0");
    }
    else
    {
        mxmlNewOpaque(node, text);
    }
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function extracts text from the XML node.
 *
 *  The function extracts text from the XML node.
 *  If XML node pointer is NULL then function return NULL.
 *
 *  \param[in]   node   XML node pointer.
 *  \return text from the XML node.
 */

char* afs_xmlutils_get_node_text(mxml_node_t* node)
{
    if (node == NULL)
    {
        return NULL;
    }

    char* text = boxing_string_clone( mxmlGetOpaque( node ) );
    if ( text == NULL )
    {
        // Try again with plain text if the opaque get failed
        text = boxing_string_clone( mxmlGetText( node, NULL ) );
    }
        

    if (text == NULL)
    {
        return NULL;
    }

    boxing_string_trim(&text);

    if (boxing_string_equal("/0", text) == DFALSE)
    {
        return text;
    }
    else
    {
        boxing_string_free(text);
        return boxing_string_clone("");
    }
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function extracts integer attribute from the XML node.
 *
 *  The function extracts integer attribute from the XML node.
 *  If XML node pointer or integer storage pointer or name pointer is NULL then function return DFALSE.
 *
 *  \param[out]  int_storage   integer storage pointer.
 *  \param[in]   node          XML node pointer.
 *  \param[in]   name          name of the integer attribute.
 *  \return DTRUE if success.
 */

DBOOL afs_xmlutils_get_integer_attribute(int* int_storage, mxml_node_t* node, const char * name)
{
    if (int_storage == NULL || node == NULL || name == NULL)
    {
        return DFALSE;
    }

    const char * attribute = mxmlElementGetAttr(node, name);
    if (attribute == NULL)
    {
        return DFALSE;
    }
    *int_storage = atoi(attribute);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function extracts unsigned integer attribute from the XML node.
 *
 *  The function extracts unsigned integer attribute from the XML node.
 *  If XML node pointer or unsigned integer storage pointer or name pointer is NULL then function return DFALSE.
 *
 *  \param[out]  int_storage   integer storage pointer.
 *  \param[in]   node          XML node pointer.
 *  \param[in]   name          name of the integer attribute.
 *  \return DTRUE if success.
 */


DBOOL afs_xmlutils_get_unsigned_integer_attribute(unsigned int * int_storage, mxml_node_t * node, const char * name)
{
    if (int_storage == NULL || node == NULL || name == NULL)
    {
        return DFALSE;
    }

    const char * attribute = mxmlElementGetAttr(node, name);
    if (attribute == NULL)
    {
        return DFALSE;
    }
    *int_storage = (unsigned int)atoi(attribute);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function adds a new node with the specified text.
 *
 *  The function adds a new node with the specified text.
 *  If XML parent node pointer or new node name name pointer or text pointer is NULL then function return without adding new node.
 *
 *  \param[out]  parent_node   the parent node to which the new node will be added.
 *  \param[in]   node_name     new XML text node name.
 *  \param[in]   text          the text that will be added to the new node.
 */

void afs_xmlutils_add_new_text_node(mxml_node_t* parent_node, const char * node_name, const char * text)
{
    if (parent_node == NULL || node_name == NULL || text == NULL)
    {
        return;
    }

    mxml_node_t *new_node = mxmlNewElement(parent_node, node_name);
    afs_xmlutils_set_node_text(text, new_node);
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function adds a new node with the specified integer number.
 *
 *  The function adds a new node with the specified integer number.
 *  If XML parent node pointer or new node name name pointer is NULL or integer number less then zero then function return without adding new node.
 *
 *  \param[out]  parent_node   the parent node to which the new node will be added.
 *  \param[in]   node_name     new XML text node name.
 *  \param[in]   node_value    the integer number that will be added to the new node.
 */

void afs_xmlutils_add_new_int_node(mxml_node_t* parent_node, const char * node_name, int node_value)
{
    if (parent_node == NULL || node_name == NULL)
    {
        return;
    }

    mxml_node_t *new_node = mxmlNewElement(parent_node, node_name);

    char buffer[sizeof(uint64_t) * 8 + 1];
    sprintf(buffer, "%d", node_value);

    afs_xmlutils_set_node_text(buffer, new_node);
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function adds a new node with the specified 64 bit integer number.
 *
 *  The function adds a new node with the specified 64 bit integer number.
 *  If XML parent node pointer or new node name name pointer is NULL or 64 bit integer number less then zero then function return without adding new node.
 *
 *  \param[out]  parent_node   the parent node to which the new node will be added.
 *  \param[in]   node_name     new XML text node name.
 *  \param[in]   node_value    the 64 bit integer number that will be added to the new node.
 */

void afs_xmlutils_add_new_uint64_node(mxml_node_t* parent_node, const char * node_name, boxing_int64 node_value)
{
    if (parent_node == NULL || node_name == NULL)
    {
        return;
    }

    mxml_node_t *new_node = mxmlNewElement(parent_node, node_name);

    char buffer[sizeof(uint64_t) * 8 + 1];
    sprintf(buffer, "%lld", (signed long long)node_value);

    afs_xmlutils_set_node_text(buffer, new_node);
}


//----------------------------------------------------------------------------
/*!
 *  \brief The function extracts integer element from the XML node.
 *
 *  The function extracts integer element from the XML node.
 *  If XML node pointer or integer storage pointer or name pointer is NULL then function return DFALSE.
 *
 *  \param[out]  int_storage   integer storage pointer.
 *  \param[in]   node          XML node pointer.
 *  \param[in]   name          name of the integer element.
 *  \return DTRUE if success.
 */

DBOOL afs_xmlutils_get_integer_element(int* int_storage, mxml_node_t* node, const char * name)
{
    if (int_storage == NULL || node == NULL || name == NULL)
    {
        return DFALSE;
    }

    mxml_node_t * integer_node = mxmlFindElement(node, node, name, NULL, NULL, MXML_DESCEND);
    if (integer_node == NULL)
    {
        return DFALSE;
    }

    char * node_text = afs_xmlutils_get_node_text(integer_node);

    if (node_text == NULL)
    {
        return DFALSE;
    }

    *int_storage = atoi(node_text);
    boxing_string_free(node_text);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
  * \} end of utils group
  */
