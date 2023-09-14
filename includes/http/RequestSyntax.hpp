#ifndef REQUESTSYNTAX_HPP
#define REQUESTSYNTAX_HPP

#include "Core.hpp"
#include "Request.hpp"

enum eStatustCode
{
	INFORMATIONAL_CONTINUE = 100,
	INFORMATIONAL_SWITCHING_PROTOCOLS = 101,
	SUCCESSFUL_OK = 200,
	SUCCESSFUL_CREATERD = 201,
	SUCCESSFUL_ACCEPTED = 202,
	SUCCESSFUL_NON_AUTHORITATIVE_INFORMATION = 203,
	SUCCESSFUL_NO_CONTENT = 204,
	SUCCESSFUL_RESET_CONTENT = 205,
	SUCCESSFUL_PARTIAL_CONTENT = 206,
	REDIRECTION_MULTIPLE_CHOICES = 300,
	REDIRECTION_MOVED_PERMANENTLY = 301,
	REDIRECTION_FOUND = 302,
	REDIRECTION_SEE_OTHER = 303,
	REDIRECTION_NOT_MODIFIED = 304,
	REDIRECTION_USE_PROXY = 305,
	REDIRECTION_UNUSED = 306,
	REDIRECTION_TEMPORARY_REDIRECT = 307,
	REDIRECTION_PERMANENT_REDIRECT = 308,
	CLIENT_ERROR_BAD_REQUEST = 400,
	CLIENT_ERROR_UNAUTHORIZED = 401,
	CLIENT_ERROR_PAYMENT_REQUIRED = 402,
	CLIENT_ERROR_FORBIDDEN = 403,
	CLIENT_ERROR_NOT_FOUND = 404,
	CLIENT_ERROR_METHOD_NOT_ALLOWED = 405,
	CLIENT_ERROR_NOT_ACCEPTABLE = 406,
	CLIENT_ERROR_PROXY_AUTHENTICATION_REQUIRED = 407,
	CLIENT_ERROR_REQUEST_TIMEOUT = 408,
	CLIENT_ERROR_CONFLICT = 409,
	CLIENT_ERROR_GONE = 410,
	CLIENT_ERROR_LENGTH_REQUIRED = 411,
	CLIENT_ERROR_PRECONDITION_FAILED = 412,
	CLIENT_ERROR_CONTENT_TOO_LARGE = 413,
	CLIENT_ERROR_URI_TOO_LONG = 414,
	CLIENT_ERROR_UNSUPPORTED_MEDIA_TYPE = 415,
	CLIENT_ERROR_RANGE_NOT_SATISFIABLE = 416,
	CLIENT_ERROR_EXPECTATION_FAILED = 417,
	CLIENT_ERROR_UNUSED = 418,
	CLIENT_ERROR_MISDIRECTED_REQUEST = 421,
	CLIENT_ERROR_UNPROCESSABLE_CONTENT = 422,
	CLIENT_ERROR_UPGRADE_REQUIRED = 426,
	SERVER_ERROR_INTERNAL_SERVER_ERROR = 500,
	SERVER_ERROR_NOT_IMPLEMENTED = 501,
	SERVER_ERROR_BAD_GATEWAY = 502,
	SERVER_SERVICE_UNAVAILABLE = 503,
	SERVER_ERROR_GATEWAY_TIMEOUT = 504,
	SERVER_ERROR_HTTP_VERSION_NOT_SUPPORTED = 505
	};

class RequestSyntax {
	public:
		RequestSyntax();
		~RequestSyntax();

		eStatustCode syntax(Request &request);
		eStatustCode method(Request& request); //mMethod
		eStatustCode requestTarget(Request& request);// mUri
		eStatustCode httpVersion(Request& request); // mVersionMajor, mVersionMinor
		eStatustCode headerField(Request& request); // mHeaders<field-name, field-value>
		eStatustCode messageBody(Request& request); // mContent
	private:
};
#endif