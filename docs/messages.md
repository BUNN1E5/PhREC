# All Supported Messages


## Message Layout
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | :--: | ---
Message ID | Data Fields | CRC-8

Messages are split into 2 different types, [Requests](#requests) and [Responses](#responses). As a general rule, the Response to a Request is exactly the bitwise NOT (~) of the Request Message ID.

For example, if a node receives a Request Hardware ID (Message ID 1 or 000001), the bitwise NOT (~) response is 111110, or -2, representing the Hardware ID Response.

## Broadcast & Addressing
Each node has a 8 bit NodeID, this can be used to send a message to a specific node.

When a node recieves a message it will first check its validity, by comparing the CRC-8 in the last 8 bits of the message with the calculated crc-8 from the first 24 bits XORed by a NodeID. If it is valid, the node accepts the message.

$$\text{CRC-8} \equiv \text{crc-8}(MessageData) \oplus \text{NodeID}$$

NodeID `000` is reserved for broadcast messages because $\text{CRC-8} \oplus \text{0} \equiv \text{CRC-8}$

A node will accept messages with its NodeID or `000`.
If a message isnt able to pass one of these checks then the message is simply dropped and ignored.

## Crosstalk

Because PhREC is a Half-Duplex RS-485 Request-Response protocol we need a way to prevent crosstalk between node in broadcast messages. We do this by defining a wait time for each node base on their Node ID and the baudrate.

$$ \text{Bits Per Frame} = \text{Start Bit} + \text{Data Bits} + \text{Parity Bits} + \text{Stop Bits} $$

$$ \text{Frame Time} = \frac{\text{Bits Per Frame}}{\text{Baud Rate}} $$

$$ \text{Wait Time} = \text{Node ID} \times \text{Frame Time} \times \text{Response Message Size}$$

### Example 1: Standard Message (Sensor Depth Request)

**Scenario:** A master node broadcasts a Request Sensor Depth (Message 5) at 115200 baud. Multiple nodes respond at staggered intervals.

**Configuration:**
- Baud Rate: 115200 bps
- UART Frame: 1 start + 8 data + 0 parity + 0.5 stop = 9.5 bits per frame
- Response Message Size: 32 bits (4 bytes)

**Calculation:**
$$\text{Frame Time} = \frac{9.5 \text{ bits}}{115200 \text{ bps}} = 0.0824 \text{ ms}$$

**Wait Times by Node ID:**
- Node 1: `1 × 0.0824 ms × 32 bits = 2.64 ms`
- Node 2: `2 × 0.0824 ms × 32 bits = 5.28 ms`
- Node 3: `3 × 0.0824 ms × 32 bits = 7.92 ms`
- Node 5: `5 × 0.0824 ms × 32 bits = 13.19 ms`

This ensures each node's response is separated by ~2.64 ms, preventing collisions.

### Example 2: Header-Data Message (Sensor Stream)

**Scenario:** Node 2 responds to a Request Sensor Data Stream (Message 11) with 4 sensors. The response consists of a header message (-12) followed by 4 sensor data frames.

**Configuration:**
- Baud Rate: 115200 bps (same frame time: 0.0824 ms)
- Header Message Size: 32 bits
- Sensor Data Message Size: 32 bits
- Total Sensor Count: 4

**Calculation for Node 2:**
- Header transmission wait time: `2 × 0.0824 ms × 32 = 5.28 ms`
- Between each sensor frame: `2 × 0.0824 ms × 32 = 5.28 ms`
- Total time to send all 4 sensor frames: `4 × 5.28 ms = 21.11 ms`

**Timeline:**
- T=0 ms: Master sends broadcast Request Sensor Data Stream (Message 11)
- T=5.28 ms: Node 2 sends Sensor Stream Header (-12) with sensor count = 4
- T=10.56 ms: Node 2 sends Sensor Data Response 1
- T=15.83 ms: Node 2 sends Sensor Data Response 2
- T=21.11 ms: Node 2 sends Sensor Data Response 3
- T=26.39 ms: Node 2 sends Sensor Data Response 4
## Requests

## 0 : Reserved for Empty Messages
This is the inital state of the message buffer, so it is defined as nothing.

## 1 : Request Hardware ID
0:5 (6b) | 6:7 (2b) | 8:23 (16b) | 24:31 (8b)
--- | --- | --- | ---
000001 | Config | Undefined | CRC-8

Requests a 16bit version of a Node's 96bit Hardware ID

When a Node has not been assigned a Node ID, response times to broadcast messages will vary based on the Hardware ID.

**Config States:**
* `00`: Default
* `01`: Auto-Assign Node ID (Valid only for broadcast)
* `10`: Reserved
* `11`: Reserved

**Response:** [-2 : Hardware ID Response](#-2--hardware-id-response)

## 2 : Assign Node ID
0:5 (6b) | 6:21 (16b) | 22:23 (2b) | 24:31 (8b)
--- | --- | --- | ---
000010 | Hardware ID | CRC-8 Checksum | $\text{CRC-8} \oplus \text{NodeID}$

Assigns a Node ID to a specific Hardware ID

If no Node ID is specified then the message is ignored.

**Checksum Encoding (Bits 22-23):**
Because the CRC-8 and NodeID share the CRC field (bits 24-31), we use a separate 2-bit checksum in bits 22-23 to validate the CRC-8 integrity:
- **Bit 22**: Checksum of CRC-8 bits 0-3 (message bits 24-27)
- **Bit 23**: Checksum of CRC-8 bits 4-7 (message bits 28-31)

This allows the receiver to detect corruption in the CRC-8 before attempting to extract the NodeID.

**Response:** [-3 : Node ID Assignment Success](#-3--node-id-assignment-success)

## 3 : Validate Node ID
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | ---
000011 | Undefined | CRC-8

Request a Node to Respond with validation.

**Response:** [-4 : Validate Node ID Response](#-4--validate-node-id-response)


## 4 : Randomize Node IDs
0:5 (6b) | 6:7 (2b) | 8:23 (16b) | 24:31 (8b)
--- | :-: | :--: | :-:
000100 | Config | Undefined | CRC-8

Requests the given Node ID to randomize its Node ID to a unused ID.

**Config States:**
* `00`: Default
* `01`: Auto-Assign Node ID (Valid only for broadcast)
* `10`: Reserved
* `11`: Reserved

**Response:** [-5 : Randomized Node ID Response](#-5--randomized-node-id-response)

## 5 : Request Sensor Depth
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | --- 
000101 | Undefined | CRC-8

Requests the total number of sensors on the target node

**Response:** [-6 : Sensor Depth Response](#-6--sensor-depth-response)

## 10 : Request Sensor Data
0:5 (6b) | 6:13 (8b) | 14:23 (10b) | 24:31 (8b)
--- | --- | --- | --- 
001010 | Sensor Depth | Undefined | CRC-8

Requests the sensor data from a specific target node up to a designated maximum number of sensors defined by sensor depth.

**Response:** [-11 : Sensor Data Response](#-11--sensor-data-response)

## 11 : Request Sensor Data Stream
0:5 (6b) | 6:13 (8b) | 14:23 (10b) | 24:31 (8b)
--- | --- | --- | --- 
001011 | Sensor Depth | Undefined | CRC-8

Requests the sensor data from a specific target node up to a designated maximum number of sensors defined by sensor depth.

**Response:** [-12 : Sensor Stream Header](#-12--sensor-stream-header) and [Sensor Stream Data](#sensor-stream-data)

## 20 : Request Motor Impulse
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | ---
010100 | Motor Strength | CRC-8

Requests the node send a impulse to its motor

# Responses

## -1 : Reserved for Empty Responses
Responses are defined by the request, and since the 000000 request is defined as nothing, the response (111111) is also nothing.

**Response to:** [0 : Reserved for Empty Messages](#0--reserved-for-empty-messages)

## -2 : Hardware ID Response
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | ---
111110 | Hardware ID | CRC-8

Broadcasts the 16 bit version of the node's hardware ID

**Response to:** [1 : Request Hardware ID](#1--request-hardware-id)

## -3 : Node ID Assignment Success
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | ---
111101 | Assigned Node ID | CRC-8

Confirms successful assignment of a Node ID to the specified Hardware ID. The response echoes back the newly assigned Node ID.

**Response to:** [2 : Assign Node ID](#2--assign-node-id)

## -4 : Validate Node ID Response

0:5 (6b) | 6:15 (10b) | 16:23 (8b) | 24:31 (8b)
--- | --- | --- | ---
111100 | 10bit Random Number | NodeID | CRC-8

Responds with a 10 bit number and the NodeID. If the CRC fails then something went wrong and either there was a bit flip or crosstalk.

In the event of crosstalk, a [4 : Randomize Node IDs](#4--randomize-node-ids) message should be sent to the NodeID to assign it a new ID and re-establish communication.

**Response to:** [3 : Validate Node ID](#3--validate-node-id)

## -5 : Randomized Node ID Response

Identical to [-4 : Validate Node ID Response](#-4--validate-node-id-response)

**Response to:** [4 : Randomize Node IDs](#4--randomize-node-ids)

## -6 : Sensor Depth Response
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | --- 
110100 | Sensor Depth | CRC-8

The number of sensors on a given Node ID

**Response to:** [5 : Request Sensor Depth](#5--request-sensor-depth)

## -11 : Sensor Data Response
0:5 (6b) | 6:23 (18b) | 24:31 (8b)
--- | --- | --- 
110101 | Sensor Data | CRC-8

A single sensor's data from a given Node ID

**Response to:** [10 : Request Sensor Data](#10--request-sensor-data)

## -12 : Sensor Stream Header
0:5 (6b) | 6:9 (4b) | 10:23 (14b) | 24:31 (8b)
--- | --- | --- | ---
111000 | Sensor Count | Undefined | CRC-8

Start signal for all sensor data

### Sensor Stream Data
0:3 (4b) | 4:23 (16b) | 24:31 (8b)
--- | --- | --- 
Sensor ID | Sensor Data | CRC-8

**Response to:** [11 : Request Sensor Data Stream](#11--request-sensor-data-stream)