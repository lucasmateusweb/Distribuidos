/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
simp_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		operands fatorial_1_arg;
		operands modulo_1_arg;
		operands max_1_arg;
		operands soma_1_arg;
		operands subtracao_1_arg;
		operands devisao_1_arg;
		operands multiplicacao_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case fatorial:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) fatorial_1_svc;
		break;

	case modulo:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) modulo_1_svc;
		break;

	case max:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) max_1_svc;
		break;

	case soma:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) soma_1_svc;
		break;

	case subtracao:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) subtracao_1_svc;
		break;

	case devisao:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) devisao_1_svc;
		break;

	case multiplicacao:
		_xdr_argument = (xdrproc_t) xdr_operands;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) multiplicacao_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (SIMP_PROG, SIMP_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, SIMP_PROG, SIMP_VERSION, simp_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (SIMP_PROG, SIMP_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, SIMP_PROG, SIMP_VERSION, simp_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (SIMP_PROG, SIMP_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
