#ifndef NFD_DAEMON_FW_LOAD_BALANCER_STRATEGY_HPP
#define NFD_DAEMON_FW_LOAD_BALANCER_STRATEGY_HPP

#include "strategy.hpp"
#include <boost/random/mersenne_twister.hpp>

namespace nfd {
namespace fw {
 
/*  This strategy forwards a new Interest to the lowest-cost nexthop
 *  that is not same as the downstream, and does not violate scope.
 *  Subsequent similar Interests or consumer retransmissions are suppressed
 *  until after InterestLifetime expiry.
 *
 *  \note This strategy is superceded by Best Route strategy version 2,
 *        which allows consumer retransmissions. This version is kept for
 *        comparison purposes and is not recommended for general usage.
 */
class LoadBalancerStrategyME : public Strategy
{
public:
  explicit
  LoadBalancerStrategyME(Forwarder& forwarder, const Name& name = getStrategyName());

protected:
  LoadBalancerStrategyME(Forwarder& forwarder);

public:
  static const Name&
  getStrategyName();

public:
  void
  afterReceiveInterest(const FaceEndpoint& inFace, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry) override;
//  afterReceiveInterest(const Face& inFace, const Interest& interest,
//                       const shared_ptr<pit::Entry>& pitEntry) override;

protected:
  boost::random::mt19937 m_randomGenerator;
int indexFace = 0;
int skip = 0;

};

} // namespace fw
} // namespace nfd

#endif // NFD_DAEMON_FW_BEST_ROUTE_STRATEGY_HPP
