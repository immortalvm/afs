/*****************************************************************************
**
**  Definition of the Administrative Metadata interface
**
**  Creation date:  2016/12/28
**  Created by:     Piql AS
**
**
**  Copyright (c) 2016 Piql AS. All rights reserved.
**
**  This file is part of the afs library
**
*****************************************************************************/

//  PROJECT INCLUDES
//
#include "administrativemetadata.h"
#include "boxing/platform/memory.h"
#include "boxing/string.h"
#include "xmlutils.h"
#include "mxml.h"

//  DEFINES
//
#define AFS_ADMINISTRATIVE_METADATA_TAG_COUNT 6

// PRIVATE INTERFACE
//

typedef struct afs_administrative_metadata_tag_s
{
    const char * tag;
    char **  content;
} afs_administrative_metadata_tag;

static afs_administrative_metadata_tag * get_tags_list(afs_administrative_metadata* control_data);
static const char *                      whitespace_cb(mxml_node_t *node, int where);


/*! 
  * \addtogroup cf
  * \{
  */


//----------------------------------------------------------------------------
/*!
 *  \struct     afs_administrative_metadata_s  controldata.h
 *  \brief      Administrative metadata storage.
 *
 *  \param reel_id        Reel id string.
 *  \param print_reel_id  Print reel id string.
 *  \param title          Title string.
 *  \param description    Description string.
 *  \param creator        Creator string.
 *  \param creation_date  Creation date string.
 *
 *  Structure for storing administrative metadata.
 */


// PUBLIC AFS ADMINISTRATIVE METADATA FUNCTIONS
//

//----------------------------------------------------------------------------
/*!
 *  \brief Create an administrative metadata instance.
 *
 *  Allocate memory for the afs_administrative_metadata type
 *  and initializes all structure pointers with NULL values.
 *  Return instance of allocated structure.
 *
 *  \return instance of allocated afs_administrative_metadata structure.
 */

afs_administrative_metadata * afs_administrative_metadata_create()
{
    afs_administrative_metadata * administrative_metadata = BOXING_MEMORY_ALLOCATE_TYPE(afs_administrative_metadata);
    
    administrative_metadata->reel_id = NULL;
    administrative_metadata->print_reel_id = NULL;
    administrative_metadata->title = NULL;
    administrative_metadata->description = NULL;
    administrative_metadata->creator = NULL;
    administrative_metadata->creation_date = NULL;
    
    return administrative_metadata;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Create an administrative metadata instance.
 *
 *  Allocate memory for the afs_administrative_metadata type
 *  and initialize structure data with specified input values.
 *  Return instance of allocated structure.
 *
 *  \param[in]  reel_id                  Pointer to the reel_id string.
 *  \param[in]  print_reel_id            Pointer to the print_reel_id string.
 *  \param[in]  title                    Pointer to the title string.
 *  \param[in]  description              Pointer to the description string.
 *  \param[in]  creator                  Pointer to the creator string.
 *  \param[in]  creation_date            Pointer to the creation_date string.
 *  \return instance of allocated afs_administrative_metadata structure.
 */

afs_administrative_metadata * afs_administrative_metadata_create2(
    const char* reel_id,
    const char* print_reel_id,
    const char* title,
    const char* description,
    const char* creator,
    const char* creation_date)
{
    afs_administrative_metadata * administrative_metadata = BOXING_MEMORY_ALLOCATE_TYPE(afs_administrative_metadata);
    administrative_metadata->reel_id = boxing_string_clone(reel_id);
    administrative_metadata->print_reel_id = boxing_string_clone(print_reel_id);
    administrative_metadata->title = boxing_string_clone(title);
    administrative_metadata->description = boxing_string_clone(description);
    administrative_metadata->creator = boxing_string_clone(creator);
    administrative_metadata->creation_date = boxing_string_clone(creation_date);
    return administrative_metadata;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Frees occupied memory of administrative metadata structure.
 *
 *  Frees occupied memory of all internal structure pointers and structure pointer.
 *
 *  \param[in]  administrative_metadata  Pointer to the afs_administrative_metadata structure.
 */

void afs_administrative_metadata_free(afs_administrative_metadata * administrative_metadata)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    boxing_memory_free(administrative_metadata->reel_id);
    boxing_memory_free(administrative_metadata->print_reel_id);
    boxing_memory_free(administrative_metadata->title);
    boxing_memory_free(administrative_metadata->description);
    boxing_memory_free(administrative_metadata->creator);
    boxing_memory_free(administrative_metadata->creation_date);
    boxing_memory_free(administrative_metadata);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function create a copy of input afs_administrative_metadata structure.
 *
 *  Function create a copy of input afs_administrative_metadata structure and return it.
 *  If administrative metadata structure pointer is NULL function return NULL.
 *
 *  \param[in]  administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \return new copy of afs_administrative_metadata structure or NULL.
 */

afs_administrative_metadata * afs_administrative_metadata_clone(const afs_administrative_metadata * administrative_metadata)
{
    if (administrative_metadata == NULL)
    {
        return NULL;
    }

    afs_administrative_metadata * return_administrative_metadata = afs_administrative_metadata_create();
    return_administrative_metadata->reel_id = boxing_string_clone(administrative_metadata->reel_id);
    return_administrative_metadata->print_reel_id = boxing_string_clone(administrative_metadata->print_reel_id);
    return_administrative_metadata->title = boxing_string_clone(administrative_metadata->title);
    return_administrative_metadata->description = boxing_string_clone(administrative_metadata->description);
    return_administrative_metadata->creator = boxing_string_clone(administrative_metadata->creator);
    return_administrative_metadata->creation_date = boxing_string_clone(administrative_metadata->creation_date);

    return return_administrative_metadata;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function checks two instances of the afs_administrative_metadata structures on the identity.
 *
 *  Function checks two instances of the afs_administrative_metadata structures on the identity.
 *
 *  \param[in]   administrative_metadata1  Pointer to the first instance of the afs_administrative_metadata structure.
 *  \param[in]   administrative_metadata2  Pointer to the second instance of the afs_administrative_metadata structure.
 *  \return sign of identity of the input structures.
 */

DBOOL afs_administrative_metadata_equal(const afs_administrative_metadata * administrative_metadata1, const afs_administrative_metadata * administrative_metadata2)
{
    if (administrative_metadata1 == NULL && administrative_metadata2 == NULL)
    {
        return DTRUE;
    }

    if (administrative_metadata1 == NULL || administrative_metadata2 == NULL)
    {
        return DFALSE;
    }

    if (boxing_string_equal(administrative_metadata1->reel_id, administrative_metadata2->reel_id) &&
        boxing_string_equal(administrative_metadata1->print_reel_id, administrative_metadata2->print_reel_id) &&
        boxing_string_equal(administrative_metadata1->title, administrative_metadata2->title) &&
        boxing_string_equal(administrative_metadata1->description, administrative_metadata2->description) &&
        boxing_string_equal(administrative_metadata1->creator, administrative_metadata2->creator) &&
        boxing_string_equal(administrative_metadata1->creation_date, administrative_metadata2->creation_date))
    {
        return DTRUE;
    }

    return DFALSE;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function sets a new reel id string in the administrative metadata structure.
 *
 *  Function sets a new reel id string in the administrative metadata structure.
 *
 *  \param[in] administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in] reel_id                  Reel id string.
 */

void afs_administrative_metadata_set_reel_id(afs_administrative_metadata * administrative_metadata, const char * reel_id)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    if (administrative_metadata->reel_id != NULL)
    {
        boxing_string_free(administrative_metadata->reel_id);
    }

    administrative_metadata->reel_id = boxing_string_clone(reel_id);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function sets a new print reel id string in the administrative metadata structure.
 *
 *  Function sets a new print reel id string in the administrative metadata structure.
 *
 *  \param[in] administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in] print_reel_id            Print reel id string.
 */

void afs_administrative_metadata_set_print_reel_id(afs_administrative_metadata * administrative_metadata, const char * print_reel_id)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    if (administrative_metadata->print_reel_id != NULL)
    {
        boxing_string_free(administrative_metadata->print_reel_id);
    }

    administrative_metadata->print_reel_id = boxing_string_clone(print_reel_id);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function sets a new title string in the administrative metadata structure.
 *
 *  Function sets a new title string in the administrative metadata structure.
 *
 *  \param[in] administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in] title                    Title string.
 */

void afs_administrative_metadata_set_title(afs_administrative_metadata * administrative_metadata, const char * title)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    if (administrative_metadata->title != NULL)
    {
        boxing_string_free(administrative_metadata->title);
    }

    administrative_metadata->title = boxing_string_clone(title);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function sets a new description string in the administrative metadata structure.
 *
 *  Function sets a new description string in the administrative metadata structure.
 *
 *  \param[in] administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in] description              Description string.
 */

void afs_administrative_metadata_set_description(afs_administrative_metadata * administrative_metadata, const char * description)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    if (administrative_metadata->description != NULL)
    {
        boxing_string_free(administrative_metadata->description);
    }

    administrative_metadata->description = boxing_string_clone(description);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function sets a new creator string in the administrative metadata structure.
 *
 *  Function sets a new creator string in the administrative metadata structure.
 *
 *  \param[in] administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in] creator                  Creator string.
 */

void afs_administrative_metadata_set_creator(afs_administrative_metadata * administrative_metadata, const char * creator)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    if (administrative_metadata->creator != NULL)
    {
        boxing_string_free(administrative_metadata->creator);
    }

    administrative_metadata->creator = boxing_string_clone(creator);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function sets a new creation date string in the administrative metadata structure.
 *
 *  Function sets a new creation date string in the administrative metadata structure.
 *
 *  \param[in] administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in] creation_date            Creation date string.
 */

void afs_administrative_metadata_set_creation_date(afs_administrative_metadata * administrative_metadata, const char * creation_date)
{
    if (administrative_metadata == NULL)
    {
        return;
    }

    if (administrative_metadata->creation_date != NULL)
    {
        boxing_string_free(administrative_metadata->creation_date);
    }

    administrative_metadata->creation_date = boxing_string_clone(creation_date);
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function translates the input afs_administrative_metadata structure to the XML file.
 *
 *  Function translates the input afs_administrative_metadata structure to the XML file.
 *  If translates is successful, then function return DTRUE, else function return DFALSE.
 *
 *  \param[in]   administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in]   file_name                Name of the XML file.
 *  \param[in]   compact                  If compact is DFALSE then in the resulting XML file needs to add formatting (new lines and tabs).
 *  \return DTRUE on success.
 */

DBOOL afs_administrative_metadata_save_file(afs_administrative_metadata * administrative_metadata, const char * file_name, DBOOL compact)
{
    if (file_name == NULL || administrative_metadata == NULL)
    {
        return DFALSE;
    }

    mxml_node_t *tree = mxmlNewXML("1.0");

#ifndef WIN32
    FILE * fp_save = fopen(file_name, "w+");
#else
    FILE * fp_save = fopen(file_name, "w+b");
#endif

    if (fp_save == NULL)
    {
        return DFALSE;
    }

    if (!afs_administrative_metadata_save_xml(administrative_metadata, tree))
    {
        fclose(fp_save);
        mxmlDelete(tree);
        return DFALSE;
    }

    mxmlSetWrapMargin(0);

    if (compact == DTRUE)
    {
        mxmlSaveFile(tree, fp_save, MXML_NO_CALLBACK);
    }
    else
    {
        mxmlSaveFile(tree, fp_save, whitespace_cb);
    }


    fclose(fp_save);
    mxmlDelete(tree);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function translates the input afs_administrative_metadata structure to the XML string.
 *
 *  Function translates the input afs_administrative_metadata structure to the XML string.
 *  If translates is successful, then function return resulting string, else function return NULL.
 *
 *  \param[in]   administrative_metadata     Pointer to the afs_administrative_metadata structure.
 *  \param[in]   compact                     If compact is DFALSE then in the resulting XML string needs to add formatting (new lines and tabs).
 *  \return resulting string or NULL.
 */

char * afs_administrative_metadata_save_string(afs_administrative_metadata * administrative_metadata, DBOOL compact)
{
    if (administrative_metadata == NULL)
    {
        return NULL;
    }

    struct mxml_node_s * document = mxmlNewXML("1.0");

    if (!afs_administrative_metadata_save_xml(administrative_metadata, document))
    {
        mxmlDelete(document);
        return NULL;
    }

    char * xmlString;
    mxmlSetWrapMargin(0);

    if (compact)
    {
        xmlString = mxmlSaveAllocString(document, MXML_NO_CALLBACK);
    }
    else
    {
        xmlString = mxmlSaveAllocString(document, whitespace_cb);
    }

    mxmlDelete(document);

    return xmlString;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function translates the input afs_administrative_metadata structure to the XML nodes.
 *
 *  Function translates the input afs_administrative_metadata structure to the XML nodes.
 *  If translates is successful, then function return DTRUE, else function return DFALSE.
 *
 *  \param[out]  out                      Pointer to the XML node.
 *  \param[in]   administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \return DTRUE on success.
 */

DBOOL afs_administrative_metadata_save_xml(afs_administrative_metadata * administrative_metadata, mxml_node_t * out)
{
    if (out == NULL || administrative_metadata == NULL)
    {
        return DFALSE;
    }

    mxml_node_t * administrative_metadata_node = mxmlNewElement(out, "AdministrativeMetadata");

    afs_administrative_metadata_tag * tags = get_tags_list(administrative_metadata);

    for (unsigned int i = 0; i < AFS_ADMINISTRATIVE_METADATA_TAG_COUNT; i++)
    {
        mxml_node_t * current_tag = mxmlNewElement(administrative_metadata_node, tags[i].tag);
        afs_xmlutils_set_node_text(*tags[i].content, current_tag);
    }

    boxing_memory_free(tags);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function translates the input XML file to the afs_administrative_metadata structure.
 *
 *  Function translates the input XML file to the afs_administrative_metadata structure.
 *  If translates is successful, then function return DTRUE, else function return DFALSE.
 *
 *  \param[out]  administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in]   file_name                Name of the XML file.
 *  \return DTRUE on success.
 */

DBOOL afs_administrative_metadata_load_file(afs_administrative_metadata * administrative_metadata, const char * file_name)
{
    if (file_name == NULL || administrative_metadata == NULL)
    {
        return DFALSE;
    }

#ifndef WIN32
    FILE * fp_load = fopen(file_name, "r");
#else
    FILE * fp_load = fopen(file_name, "rb");
#endif

    if (fp_load == NULL)
    {
        return DFALSE;
    }

    mxml_node_t * document = mxmlLoadFile(NULL, fp_load, MXML_OPAQUE_CALLBACK);
    
    if (document == NULL)
    {
        fclose(fp_load);
        mxmlDelete(document);

        return DFALSE;
    }
    
    DBOOL return_value = afs_administrative_metadata_load_xml(administrative_metadata, document);
    
    fclose(fp_load);
    mxmlDelete(document);

    return return_value;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function translates the input XML string to the afs_administrative_metadata structure.
 *
 *  Function translates the input XML string to the afs_administrative_metadata structure.
 *  If translates is successful, then function return DTRUE, else function return DFALSE.
 *
 *  \param[out]  administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in]   in                       Pointer to the input XML string.
 *  \return DTRUE on success.
 */

DBOOL afs_administrative_metadata_load_string(afs_administrative_metadata * administrative_metadata, const char * in)
{
    if (in == NULL || boxing_string_equal(in, "") || administrative_metadata == NULL)
    {
        return DFALSE;
    }

    mxml_node_t * document = mxmlLoadString(NULL, in, MXML_OPAQUE_CALLBACK);

    if (!afs_administrative_metadata_load_xml(administrative_metadata, document))
    {
        return DFALSE;
    }

    mxmlDelete(document);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
 *  \brief Function translates the input XML nodes to the afs_administrative_metadata structure.
 *
 *  Function translates the input XML nodes to the afs_administrative_metadata structure.
 *  If translates is successful, then function return DTRUE, else function return DFALSE.
 *
 *  \param[out]  administrative_metadata  Pointer to the afs_administrative_metadata structure.
 *  \param[in]   in                       Pointer to the input XML node.
 *  \return DTRUE on success.
 */

DBOOL afs_administrative_metadata_load_xml(afs_administrative_metadata* administrative_metadata, mxml_node_t * in)
{
    if (in == NULL || administrative_metadata == NULL)
    {
        return DFALSE;
    }

    mxml_node_t * administrative_metadata_node = mxmlFindElement(in, in, "AdministrativeMetadata", NULL, NULL, MXML_DESCEND);

    if (administrative_metadata_node == NULL)
    {
        return DFALSE;
    }

    afs_administrative_metadata_tag* tags = get_tags_list(administrative_metadata);

    for (unsigned int i = 0; i < AFS_ADMINISTRATIVE_METADATA_TAG_COUNT; i++)
    {
        mxml_node_t * current_tag_node = mxmlFindElement(administrative_metadata_node, administrative_metadata_node, tags[i].tag, NULL, NULL, MXML_DESCEND);

        if (current_tag_node == NULL)
        {
            boxing_memory_free(tags);
            return DFALSE;
        }

        *tags[i].content = afs_xmlutils_get_node_text(current_tag_node);
    }

    boxing_memory_free(tags);

    return DTRUE;
}


//----------------------------------------------------------------------------
/*!
  * \} end of cf group
  */


// PRIVATE AFS ADMINISTRATIVE METADATA FUNCTIONS
//

static afs_administrative_metadata_tag * get_tags_list(afs_administrative_metadata * control_data)
{
    afs_administrative_metadata_tag * tags = BOXING_MEMORY_ALLOCATE_TYPE_ARRAY(afs_administrative_metadata_tag, AFS_ADMINISTRATIVE_METADATA_TAG_COUNT);
    tags[0].tag = "ReelId";
    tags[0].content = &control_data->reel_id;

    tags[1].tag = "PrintReelId";
    tags[1].content = &control_data->print_reel_id;

    tags[2].tag = "Title";
    tags[2].content = &control_data->title;

    tags[3].tag = "Description";
    tags[3].content = &control_data->description;

    tags[4].tag = "Creator";
    tags[4].content = &control_data->creator;

    tags[5].tag = "CreationDate";
    tags[5].content = &control_data->creation_date;

    return tags;
}


static const char * whitespace_cb(mxml_node_t * node, int where)
{
    const char * name, * parent_name;

    /*
    * We can conditionally break to a new line
    * before or after any element. These are
    * just common HTML elements...
    */

    name = mxmlGetElement(node);
    parent_name = mxmlGetElement(node->parent);

    if (boxing_string_equal("AdministrativeMetadata", name))
    {
        if (where == MXML_WS_BEFORE_OPEN || where == MXML_WS_BEFORE_CLOSE)
        {
            return ("\n");
        }
    }

    if (boxing_string_equal("AdministrativeMetadata", parent_name))
    {
        if (where == MXML_WS_BEFORE_OPEN || where == MXML_WS_BEFORE_CLOSE)
        {
            return ("\n    ");
        }

        if (where == MXML_WS_AFTER_OPEN)
        {
            return ("\n        ");
        }
    }

    return (NULL);
}
