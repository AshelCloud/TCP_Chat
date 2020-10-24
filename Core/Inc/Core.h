#pragma once

#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>

#include<memory>
#include<algorithm>
#include<vector>
#include<map>
#include<iostream>
#include<string>

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;

#include"SocketAddress.h"
#include"SocketAddressFactory.h"
#include"TCPSocket.h"
#include"SocketUtil.h"