# All Supported Messages

### General Message Layout

Messages are communication between nodes. Broadcast messages are received by all nodes. To avoid cross-talk, node response time will vary based on the Node ID.

Some message types require a Node ID to be sent to a specific node. Using Node ID `000` will send it as a broadcast message.

The first 6 bits of a message are reserved for the Message ID. The remaining bits have different definitions based on the Message ID.

0:5 (6b) | 6:31 (26b)
--- | :--: 
Message ID | Based on Message ID

Messages are split into 2 different types, [Requests](#requests) and [Responses](#responses). As a general rule, the Response to a Request is exactly the bitwise NOT (~) of the Request Message ID.

For example, if a node receives a Request Hardware ID (Message ID 1 or 000001), the bitwise NOT (~) response is 111110, or -2, representing the Hardware ID Response.



## Requests

### 0 : Reserved for Empty Messages
This is the inital state of the message buffer, so it is defined as nothing.

### 1 : Request Hardware ID
0:5 (6b) | 6:13(8b) | 14:15(2b) | 16:23 (8b) | 24:31 (8b)
--- | --- | --- | --- | ---
000001 | Node ID | Config | Node ID Offset | Undefined

Requests a node's last 16 bits of its Hardware ID. 

A node will respond with the message [-2 : Hardware ID Response](#-2--hardware-id-response).

When a Node has not been assigned a Node ID, response times to broadcast messages will vary based on the Hardware ID.

Config States:
- 00 : Default
  - TODO :: ADD EXP
- 01 : Auto Assign Node ID
  - This configuration is only valid when the message is broadcast
  - Requests the node to determine its own node ID based on all responses and Node ID offset.
  - Node ID offset is only valid in this mode
- 10 : Undefined
- 11 : Undefined

### 2 : Assign Node ID
0:5 (6b) | 6:13 (8b) | 14:29 (16b) | 30:31 (2b)
--- | --- | --- | ---
000010 | Node ID | Hardware ID | Undefined 

Assigns a Node ID to a specific Hardware ID

This request does not have a response

### 3 : Validate Node IDs
0:5 (6b) | 6:31 (26b)
--- | ---
000011 | Undefined

Broadcasts a request to all nodes to respond with a random 8bit number and a CRC-8.
Each node will respond with a [-4 : Validate Node ID Response](#-4--validate-node-id-response)


### 4 : Randomize Node IDs
0:5 (6b) | 6:13 (8b) | 14:15 (2b) | 16:31 (16b)
--- | :-: | :--: | :-:
000100 | Node ID | Config | Undefined

Requests the given Node ID to randomize its Node ID to a unused ID. The node will respond with [-5 : Randomized Node ID Response](#-5--randomized-node-id-response)

Configuration State:
- 00 : Default
- 01 : Auto Compress Node ID
  - Requests the node to assign itself a Node ID the lowest available Node ID 
- 10 : Undefined
- 11 : Undefined

### 5 : Request Sensor Depth
0:5 (6b) | 6:13 (8b) | 14:31 (18b) 
--- | --- | --- 
001010 | Node ID | Undefined

Requests the total number of sensors on the target node

### 10 : Request Sensor Data
0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 22:31 (10b)
--- | --- | --- | --- 
000111 | Node ID | Sensor Depth | Undefined

Requests the sensor data from a specific target node up to a designated maximum number of sensors defined by sensor depth

Each sensor will send its own [-11 : Sensor Data Response](#-11--sensor-data-response)

### 11 : Request Sensor Data Stream
0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 22:31 (10b)
--- | --- | --- | --- 
000111 | Node ID | Sensor Depth | Undefined

Requests the sensor data from a specific target node up to a designated maximum number of sensors defined by sensor depth.

Each sensor will send a single [-12 : Sensor Stream Header](#-12--sensor-stream-header) and then a [-13 : Sensor Stream Data](#-13--sensor-stream-data) for each sensor

### 20 : Request Motor Impulse
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | ---
010100 | Node ID | Motor Strength

Requests the node send a impulse to its motor

## Responses

### -1 : Reserved for Empty Responses
Responses are defined by the request, and since the 000000 request is defined as nothing, the response (111111) is also nothing.

### -2 : Hardware ID Response
0:5 (6b) | 6:13 (16b) | 14:31 (18b)
--- | --- | ---
111110 | Node ID | Hardware ID 

Broadcasts the last 16 bits hardware ID of the node

if Node ID is not defined yet then it will respond with a `000`

### -3 : UNDEFINED

### -4 : Validate Node ID Response

0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 22:29 (8b) | 30:31 (2b)
--- | --- | --- | --- | ---
111100 | Node ID | 8bit Random Number | CRC-8 | Undefined

TODO :: FIX ME
Waits Node ID time and responds with a node ID and a CRC-8 of the Node ID. If the CRC-8 fails then we have a collision and the Node ID needs to be reassigned

### -5 : Randomized Node ID Response

0:5 (6b) | 6:13 (8b) | 14:21 (8b) | 22:31 (10b)
--- | --- | --- | ---
111011 | Node ID | CRC-8 | Undefined

Identical to -4 Validate Node ID Response

### -6 : Sensor Depth Response
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110100 | Node ID | Sensor Depth

The number of sensors on a given Node ID

### -11 : Sensor Data Response
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110101 | Node ID | Sensor Data

A single sensor's data from a given Node ID

### -12 : Sensor Stream Header
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110101 | Node ID | Sensor Count

Start signal for all sensor data

### -13 : Sensor Stream Data
0:5 (6b) | 6:13 (8b) | 14:31 (18b)
--- | --- | --- 
110110 | Sensor ID | Sensor Data

Sensor data for the node indicated in the last [-12 : Sensor Stream Header](#-12--sensor-stream-header) message