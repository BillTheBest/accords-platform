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
#ifndef	_element_c
#define	_element_c

#include "standard.h"
#include "element.h"

public	struct	xml_atribut * liberate_atribut(struct xml_atribut * aptr)
{
	if ( aptr )
	{
		if ( aptr->name )
			liberate( aptr->name );
		if ( aptr->value )
			liberate( aptr->value );
		liberate( aptr );
	}
	return( (struct xml_atribut *) 0 );
}

public	struct	xml_atribut * allocate_atribut()
{
	struct	xml_atribut * aptr;
	if (!(aptr = (struct xml_atribut*) allocate(sizeof( struct xml_atribut ))))
		return( aptr );
	else
	{
		aptr->previous = 
		aptr->next = (struct xml_atribut *) 0;
		aptr->value = aptr->name = (char *) 0;
		return( aptr );
	}
}

void	add_atribut( struct xml_element * eptr, struct xml_atribut * aptr )
{
	if ( eptr )
	{
		if ( aptr )
		{
			if (!( aptr->previous = eptr->lastatb ))
				eptr->firstatb = aptr;
			else	aptr->previous->next = aptr;
			eptr->lastatb = aptr;
		}
	}
	return;
}

public	struct	xml_element * liberate_element(struct xml_element * eptr)
{
	struct	xml_atribut * aptr;
	struct	xml_element * wptr;

	if ( eptr )
	{
		while ((wptr = eptr->first) != (struct xml_element *) 0)
		{
			eptr->first = wptr->next;
			wptr = liberate_element( wptr );
		}
		while ((aptr = eptr->firstatb) != (struct xml_atribut *) 0)
		{
			eptr->firstatb = aptr->next;
			aptr = liberate_atribut( aptr );
		}
		if ( eptr->name )
			liberate( eptr->name );
		if ( eptr->value )
			liberate( eptr->value );
		liberate( eptr );

	}
	return( (struct xml_element *) 0 );
}

public	struct	xml_element  * allocate_element()
{
	struct	xml_element * eptr;
	if (!(eptr = (struct xml_element*) allocate(sizeof( struct xml_element ))))
		return( eptr );
	else
	{
		eptr->payload = (void *) 0;
		eptr->previous = 
		eptr->next =
		eptr->parent =
		eptr->first =
		eptr->last = (struct xml_element *) 0;
		eptr->firstatb =
		eptr->lastatb = (struct xml_atribut *) 0;
		eptr->name = 
		eptr->value = (char *) 0;
		return( eptr );
	}
};


void	add_element( struct xml_element * eptr, struct xml_element * aptr )
{
	if ( eptr )
	{
		if ( aptr )
		{
			if (!( aptr->previous = eptr->last ))
				eptr->first = aptr;
			else	aptr->previous->next = aptr;
			eptr->last = aptr;
			aptr->parent = eptr;
		}
	}
	return;
}

void	show_element( struct xml_element * eptr )
{
	struct	xml_atribut * aptr;
	struct	xml_element * wptr;
	printf("<%s",eptr->name);
	if ( eptr->firstatb )
	{
		for (	aptr=eptr->firstatb;
			aptr != (struct xml_atribut *) 0;
			aptr = aptr->next )
		{
			printf(" %s='%s'",aptr->name,(aptr->value?aptr->value:"\0"));
		}
	}
	if ((!( eptr->first )) && (!( eptr->value )))
		printf("/>\n");
	else
	{
		printf(">");
		if ( eptr->first )
		{
			for (	wptr=eptr->first;
				wptr != (struct xml_element *) 0;
				wptr = wptr->next )
				show_element( wptr );
		}
		if ( eptr->value )
			printf("%s",eptr->value);
		printf("</%s>\n",eptr->name);
	}
	return;
}
	
int	extend_value( char ** vptr, char * tptr, int tlen )
{
	int	rlen=0;	
	char *	rptr;
	char *	sptr;
	if (!( vptr ))
		return( 118 );
	else if (!( tptr ))
		return( 118 );
	else if (!( tlen ))
		return(0);
	else 
	{
		sptr = *vptr;
		rlen = tlen + (sptr ? strlen(sptr) : 0 );
		if (!( rptr = allocate( rlen + 1 ) ))
			return( 27 );
		else 
		{
			sprintf(rptr,"%s%s",(sptr ? sptr : "\0"),tptr);
			*vptr = rptr;
			if ( sptr )
				liberate( sptr );
			return( 0);
		}
	}
}

#endif	/* _element_c */
	/* ---------- */


