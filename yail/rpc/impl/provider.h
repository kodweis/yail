#ifndef YAIL_RPC_IMPL_PROVIDER_H
#define YAIL_RPC_IMPL_PROVIDER_H

#include <yail/rpc/detail/provider_impl.h>

namespace yail {
namespace rpc {

template <typename Transport>
provider<Transport>::provider (service<Transport> &service, const std::string &service_name) :
	m_impl (make_unique <impl_type> (service.get_impl (), service_name))
{
	YAIL_LOG_FUNCTION (this << service_name);
}

template <typename Transport>
provider<Transport>::~provider ()
{
	YAIL_LOG_FUNCTION (this);
}

template <typename Transport> 
template <typename Request, typename Response, typename Handler>
void provider<Transport>::add_rpc (const rpc<Request, Response> &service_rpc, const Handler &handler)
{
	m_impl->add_rpc (service_rpc.get_impl (), handler);
}

template <typename Transport> 
template <typename Request, typename Response>
void provider<Transport>::reply_ok (yail::rpc::trans_context &tctx, const rpc<Request, Response> &service_rpc, const Response &res)
{
	m_impl->reply_ok (tctx, service_rpc.get_impl (), res);
}

template <typename Transport> 
template <typename Request, typename Response>
void provider<Transport>::reply_error (yail::rpc::trans_context &tctx, const rpc<Request, Response> &service_rpc, const std::string &errmsg)
{
	m_impl->reply_error (tctx, service_rpc.get_impl (), errmsg);
}

template <typename Transport> 
template <typename Request, typename Response>
void provider<Transport>::reply_delayed (yail::rpc::trans_context &tctx, const rpc<Request, Response> &service_rpc)
{
	m_impl->reply_delayed (tctx, service_rpc.get_impl ());
}

} // namespace rpc
} // namespace yail

#endif // YAIL_RPC_IMPL_PROVIDER_H
