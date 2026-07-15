# Network Initalization Protocol

When initalizing the PhREC network we need to have a method to prevent each node from talking over eachother. To prevent this, each node is given a Unique ID and from that ID a wait time is derived to be used on responses from broadcast messages. Most messages are broadcast so this should be fine for us.

The network setup is done in a couple steps:

## Unique ID Generation

The manager broadcasts a message to all nodes requesting them to repond with 16bits of their Hardware ID. 

## Registration

Each node then waits for a time derived by their Hardware ID, and informs the manager and every other node of it's Hardware ID. 

## Collision Validation

Because there is always a chance for collisions (0.0015% chance at 16bit ID). We still want to do at least a single validation step to really make sure noone has the same ID.

The manager will request each node to respond with a random number and a CRC hash, if the hash fails then we have a collision and the manager requests that node to be reassigned.

## Final ID Assignment

Now that we know there are no collisions. The manager will either broadcast a message to have all node pack their own IDs or we have the manager assign them (I haven't decided yet)
