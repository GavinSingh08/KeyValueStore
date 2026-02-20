# Key-Value Store

An interactive console-based key-value database built in C++.  
Supports basic operations, TTL-based key expiration, and file persistence.

---

## Features

- **SET key value [EX seconds]**: Store a key-value pair. Optional `EX` sets a TTL (time-to-live) in seconds.  
- **GET key**: Retrieve the value of a key if it exists and hasn't expired.  
- **DEL key**: Delete a key from the store.  
- **TTL expiration**: Keys can automatically expire after a specified number of seconds.  
- **Persistence**: Keys are saved to a file on exit and loaded on startup (`key_vals.txt`).  

---

## Example Usage

```text
> SET session abc EX 5
Key: session | Value: abc | With expiration: 5 seconds

> GET session
abc

(wait 5 seconds)

> GET session
Key expired

> DEL session
Deleting: session

> EXIT
