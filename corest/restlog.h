#ifndef	_rest_log_h
#define	_rest_log_h


public	int	rest_log_send_request ( char * agent, char * method, struct url * uptr );
public	int	rest_log_recv_response( char * agent, struct rest_response * aptr );

public	int	rest_log_send_response( char * agent, struct rest_response * aptr );
public	int	rest_log_recv_request ( char * agent, struct rest_request  * rptr );

public	int	rest_log_message( char * message );
public	int	rest_log_warning( char * message );
public	int	rest_log_failure( char * message );
public	int	rest_log_transaction( char * message );
public	int	rest_log_debug( char * message );
public	int	rest_log_file( char * message );

public	char *	rest_log_comons_identity(char * category, char * agent, char * tls);


	/* ---------- */
#endif	/* _restlog_h */
	/* ---------- */

