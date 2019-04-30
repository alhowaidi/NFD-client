#include "load-balancer-strategy.hpp"
#include "algorithm.hpp"
#include <boost/random/uniform_int_distribution.hpp>

namespace nfd {
namespace fw {

LoadBalancerStrategyME::LoadBalancerStrategyME(Forwarder& forwarder)
  : Strategy(forwarder)
{
}

void
LoadBalancerStrategyME::afterReceiveInterest(const FaceEndpoint& inFace, const Interest& interest,
                                            const shared_ptr<pit::Entry>& pitEntry)
{ 
  if (hasPendingOutRecords(*pitEntry)) {
    // not a new Interest, don't forward
    return;
  }
  
  const fib::Entry& fibEntry = this->lookupFib(*pitEntry);
  const fib::NextHopList& nexthops = fibEntry.getNextHops();

auto segmentNo = 0;
// if (!interest.getCanBePrefix()) {
if(skip != 0 )  
{
segmentNo = static_cast<size_t>(interest.getName()[-1].toSegment());
} else {
std::cout << "skip now " << std::endl;
skip = skip + 1;
}
//int firstPathPipline = 10;
//int secondPathPipline = 10;
// int thirdPathPipline = 10;

//int secondLimit = firstPathPipline + secondPathPipline;
//int thirdLimit = secondLimit + thirdPathPipline;
  
  fib::NextHopList::const_iterator selected;
//int foo [10] = {0,0,0,0,0,1,1,1,2,2}; // i guess this one was for ratio
//  boost::random::uniform_int_distribution<> dist(0, nexthops.size() - 1);
 // const size_t randomIndex = foo[(indexFace%10)];//%(nexthops.size()*10));  
// const size_t randomIndex = (indexFace%nexthops.size());//%(nexthops.size()*10));  
 size_t randomIndex = 0; // = (indexFace/80);//%(nexthops.size()*10));  

if( segmentNo <= 40000)
{
	if(skip == 1) {
		std::cout << "face 1" << std::endl;
		skip = 2;
	}

	randomIndex = 0;
} 
else if(40000 < segmentNo && segmentNo <= 80000)
{ 
	if(skip == 2) {
		std::cout << "face 2" << std::endl;
		skip = 3;
	}
	randomIndex = 1;
}
else
{
	if(skip == 3) {
		std::cout << "face 3" << std::endl;
		skip = 4;
	}

	 randomIndex = 2;
 }

//std::cout << segmentNo << "   " << randomIndex << std::endl;
/*if(0 <=indexFace && indexFace <= firstPathPipline)
{ 
  randomIndex = 0;
}
else if(firstPathPipline < indexFace && indexFace <= secondLimit )
{
  randomIndex = 1;
}
else if(secondLimit < indexFace && indexFace <= thirdLimit)
{
  randomIndex = 2;
}


indexFace++; 

if(indexFace == thirdLimit)
  indexFace = 0;
*/

//if(indexFace == nexthops.size())
//if(indexFace == (nexthops.size()*80))
//if(indexFace == 10)
////////////////////////////indexFace = 0;
//std::cout <<"indexFAce : " << indexFace << std::endl;
//std::cout <<"size: "<< nexthops.size() << std::endl;
//std::cout <<"index: "<< randomIndex << std::endl;
  uint64_t currentIndex = 0;
  
  for (selected = nexthops.begin(); selected != nexthops.end(); ++selected, ++currentIndex)
{
	if (currentIndex == randomIndex) {
		Face& outFace = selected->getFace();
		//aut outFace = FaceEndpoint(selected->getFace(), 0);
		//std::cout << outFace.getRemoteUri() << std::endl;
		if (!wouldViolateScope(inFace.face, interest, outFace) &&
				canForwardToLegacy(*pitEntry, outFace)) {
			//      std::cout << outFace.getRemoteUri() << std::endl;
			this->sendInterest(pitEntry, FaceEndpoint(outFace,0), interest);
			return;
		}else{
			std::cout << " in else " << std::endl;
		}
	}
}
std::cout << "rejected " << std::endl;
this->rejectPendingInterest(pitEntry);
}
//NFD_LOG_INIT("LoadBalancerStrategyME");
NFD_REGISTER_STRATEGY(LoadBalancerStrategyME);

LoadBalancerStrategyME::LoadBalancerStrategyME(Forwarder& forwarder, const Name& name)
  : Strategy(forwarder)
{
  ParsedInstanceName parsed = parseInstanceName(name);
  if (!parsed.parameters.empty()) {
    BOOST_THROW_EXCEPTION(std::invalid_argument("BestRouteStrategy does not accept parameters"));
  }
  if (parsed.version && *parsed.version != getStrategyName()[-1].toVersion()) {
    BOOST_THROW_EXCEPTION(std::invalid_argument(
      "BestRouteStrategy does not support version " + std::to_string(*parsed.version)));
  }
  this->setInstanceName(makeInstanceName(name, getStrategyName()));
}

const Name&
LoadBalancerStrategyME::getStrategyName()
{
  static Name strategyName("/localhost/nfd/strategy/load-balancer/%FD%01");
  return strategyName;
}

} // namespace fw
} // namespace nfd


