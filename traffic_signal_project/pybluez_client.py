import sys
import bluetooth

print("Performing inquiry...")

nearby_devices = bluetooth.discover_devices(duration=8, lookup_names=True,
                                            flush_cache=True, lookup_class=False)

print("Found {} devices".format(len(nearby_devices)))

hotmega_name = None
hotmega_addr = None

for addr, name in nearby_devices:
    try:
        print("   {} - {}".format(addr, name))
        if name == "Hotmega128":
            hotmega_uuid = name
            hotmega_addr = addr

    except UnicodeEncodeError:
        print("   {} - {}".format(addr, name.encode("utf-8", "replace")))


if len(sys.argv) < 2:
    print("No device specified. Searching all nearby bluetooth for the Sample Server service")
else:
    addr = sys.argv[1]
    print("Searching for Sample Server on {}...".format(addr))


print("name : {}    -   addr : {}".format(hotmega_name, hotmega_addr))

service_matches = bluetooth.find_service(name=hotmega_name, address=hotmega_addr)

if len(service_matches) == 0:
    print("Couldn't find the Sample server service.")
    sys.exit(0)

first_match = service_matches[0]

port = first_match["port"]
name = first_match["name"]
host = first_match["host"]

print("Connecting to \"{}\" on {}".format(name, host))

sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((host, port))

print("Connected. Type something...")

while True:
    data = input()
    if not data:
        break
    sock.send(data)

sock.close()