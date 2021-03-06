/* -------------------------------------------------------------------- */
/*  ACCORDS PLATFORM                                                    */
/*  (C) 2011 by Iain James Marshall (Prologue) <ijm667@hotmail.com>     */
/* -------------------------------------------------------------------- */
/* Licensed under the Apache License, Version 2.0 (the "License"); 	*/
/* you may not use this file except in compliance with the License. 	*/
/* You may obtain a copy of the License at 				*/
/*  									*/
/*  http://www.apache.org/licenses/LICENSE-2.0 				*/
/*  									*/
/* Unless required by applicable law or agreed to in writing, software 	*/
/* distributed under the License is distributed on an "AS IS" BASIS, 	*/
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 	*/
/* implied. 								*/
/* See the License for the specific language governing permissions and 	*/
/* limitations under the License. 					*/
/* -------------------------------------------------------------------- */
#ifndef	_parser_c
#define	_parser_c

#include "standard.h"
#include "parser.h"
#include "rest.h"
#include "occi.h"
#include "document.h"
#include "cordspublic.h"
#include "occipublisher.h"
#include "occibuilder.h"
#include "cordslang.h"

struct	accords_configuration Parser = {
	0,0,
	0,0,0,0,
	(char *) 0,
	(char *) 0,
	_CORDS_DEFAULT_PUBLISHER,
	_CORDS_DEFAULT_OPERATOR,
	_CORDS_DEFAULT_USER,
	_CORDS_DEFAULT_PASSWORD,
	"http",  80,
	"xmpp",  8000,
	"domain",
	"parser.xml",
	"europe",
	"storage",
	"parser",
	(struct occi_category *) 0,
	(struct occi_category *) 0
	};

public	int	check_debug()		{	return(Parser.debug);		}
public	int	check_verbose()		{	return(Parser.verbose);		}
public	char *	default_publisher()	{	return(Parser.publisher);	}
public	char *	default_operator()	{	return(Parser.operator);	}
public	char *	default_tls()		{	return(Parser.tls);		}
public	char *	default_zone()		{	return(Parser.zone);		}

public	int	failure( int e, char * m1, char * m2 )
{
	if ( e )
	{
		printf("\n*** failure %u",e);
		if ( m1 )
			printf(" : %s",m1);
		if ( m2 )
			printf(" : %s",m2);
		printf(" **`\n");
	}
	return( e );
}

/*	---------------------------------------------	*/  
/*			p a r s e r _ l o a d 		*/
/*	---------------------------------------------	*/
/*	this function loads parser    configuration	*/
/*	from the xml configuration file.		*/
/*	---------------------------------------------	*/  
private	void	parser_load()
{
	load_accords_configuration( &Parser, "parser" );
	return;
}

private	int	banner()
{
	printf("\n   CompatibleOne Request Parser : Version 1.0a.0.09");
	printf("\n   Beta Version : 20/10/2013");
	printf("\n   Copyright (c) 2011, 2013 Iain James Marshall, Prologue");
	printf("\n");
	accords_configuration_options();
	printf("\n\n");
	return(0);

}

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ i n i t i a l i s e			*/
/*	------------------------------------------------------------------	*/
private	struct rest_server * parser_initialise(  void * v,struct rest_server * sptr )
{
	struct	rest_extension * xptr;
	if (!( xptr = rest_add_extension( sptr ) ))
		return((struct rest_server *) 0);
	else
	{
		xptr->net = (struct connection *) 0;
		return( sptr );
	}
}

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ a u t h o r i s e 			*/
/*	------------------------------------------------------------------	*/
private	int	parser_authorise(  void * v,struct rest_client * cptr, char * username, char * password )
{
	if ( strcmp( username, Parser.user ) )
		return(0);
	else if ( strcmp( password, Parser.password ) )
		return(0);
	else if (!( cptr->user = allocate_string( username ) ))
		return(0);
	else if (!( cptr->pass = allocate_string( password ) ))
		return(0);
	else	return(1);
}

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ e x t e n s i o n 			*/
/*	------------------------------------------------------------------	*/
private	struct rest_extension * parser_extension( void * v,struct rest_server * sptr, struct rest_extension * xptr)
{
	return( xptr );
}

/*	------------------------------------------------------------------	*/
/*			b r o k e r _ o p e r a t i o n				*/
/*	------------------------------------------------------------------	*/
private	int	parser_operation( char * nptr )
{
	struct	occi_category * first=(struct occi_category *) 0;
	struct	occi_category * last=(struct occi_category *) 0;
	struct	occi_category * optr=(struct occi_category *) 0;

	set_autosave_cords_xlink_name("links_parser.xml");

	if (!( optr = occi_cords_manifest_builder( Parser.domain, _CORDS_MANIFEST ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if ( Parser.autopub )
		optr->access   |= _OCCI_AUTO_PUBLISH;

	if (!( optr = occi_cords_configuration_builder( Parser.domain, _CORDS_CONFIGURATION ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_release_builder( Parser.domain, _CORDS_RELEASE ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	if (!( optr = occi_cords_interface_builder( Parser.domain, _CORDS_INTERFACE ) ))
		return( 27 );
	else if (!( optr->previous = last ))
		first = optr;
	else	optr->previous->next = optr;
	last = optr;
	optr->callback  = (void *) 0;

	rest_initialise_log( Parser.monitor );

	if (!( Parser.identity ))
		return( occi_server(  nptr, Parser.restport, Parser.tls, Parser.threads, first, (char *) 0 ) );
	else
	{
		initialise_occi_publisher( Parser.publisher, (char*) 0, (char *) 0, (char *) 0);
		return( publishing_occi_server(
			Parser.user, Parser.password,
			Parser.identity,  nptr, 
			Parser.restport, Parser.tls, 
			Parser.threads, first ) );
	}
}

/*	------------------------------------------------------------------	*/
/*				b r o k e r 					*/
/*	------------------------------------------------------------------	*/
private	int	parser(int argc, char * argv[] )
{
	int	status=0;
	int	argi=0;
	char *	aptr;
	parser_load();
	while ( argi < argc )
	{
		if (!( aptr = argv[++argi] ))
			break;
		else if ( *aptr == '-' )
		{
			aptr++;
			switch( *(aptr++) )
			{
			case	'v'	:
				Parser.verbose=1;
				continue;
			case	'd'	:
				Parser.debug = 0xFFFF;
				continue;
			case	'-'	:
				if (!( argi = accords_configuration_option( aptr, argi, argv )))
					break;
				else	continue;
			}
			status = 30;
			break;
		}
		else if (!( status = parser_operation(aptr) ))
			continue;
		else	break;
	}
	return(status);
}

/*	------------------------------------------------------------------	*/
/*					m a i n 				*/
/*	------------------------------------------------------------------	*/
public	int	main(int argc, char * argv[] )
{
	if ( argc == 1 )
		return( banner() );
	else	return( parser( argc, argv ) );
}


	/* --------- */
#endif	/* _parser_c */
	/* --------- */

