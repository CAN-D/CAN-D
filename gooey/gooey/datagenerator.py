import cantools
import random


def formatHexData(s):
    return (" ".join(s[i:i+2] for i in range(0, len(s), 2))).upper()


def formatId(id):
    return id[0:2] + id[2:len(id)].upper()


db = cantools.database.load_file(
    '/Users/enzozafra/Documents/Projects/CAN-D/dbc/is350.dbc')

for m in db.messages:
    data = {}
    for s in m.signals:
        data[s.name] = abs(random.uniform(s._minimum, (s._maximum/3)))
    encoded = m.encode(data)
    temp = encoded.hex()
    arbid = hex(m._frame_id)
    msg = formatId(arbid) + " " + formatHexData(temp)
    print(msg)
