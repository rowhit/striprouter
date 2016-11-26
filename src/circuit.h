#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <mutex>

#include <Eigen/Core>

#include "int_types.h"
#include "via.h"


extern std::mutex circuitMutex;

// Packages

typedef std::vector<Via> PackageRelCoordVec;
typedef std::map<std::string, PackageRelCoordVec> PackageToCoordMap;

// Components

class Component {
public:
  Component();
  Component(const std::string&, const Via&);
  std::string packageName;
  Via pin0AbsCoord;
};

typedef std::map<std::string, Component> ComponentNameToInfoMap;

// Connections

class ConnectionPoint {
public:
  ConnectionPoint(const std::string&, u32 _pinIdx);
  std::string componentName;
  u32 pinIdx;
};

class Connection {
public:
  Connection(const ConnectionPoint& _start, const ConnectionPoint& _end);
  ConnectionPoint start;
  ConnectionPoint end;
};

// Circuit

typedef std::vector<Connection> ConnectionVec;
typedef std::vector<ViaStartEnd> ConnectionViaVec;
typedef std::vector<std::string> CircuitInfoVec;
typedef std::vector<Via> PinViaVec;

class Circuit {
public:
  Circuit();

  ConnectionViaVec genConnectionViaVec();
  ViaStartEnd calcComponentFootprint(std::string componentName);
  PinViaVec calcComponentPins(std::string componentName);

  PackageToCoordMap packageToCoordMap;
  ComponentNameToInfoMap componentNameToInfoMap;
  ConnectionVec connectionVec;
  CircuitInfoVec circuitInfoVec;
  bool hasError;
private:
  Via connectionFudge(const std::string& componentName, const Via& absPin);
};