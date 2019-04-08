class GpsController(object):
""" 
    A controller for the GPS tab view, containing the data for the view

    :param `gpsdata`: an array containing GPS coordinates
"""

def __init__(self, gpsdata=None):
    if gpsdata is not None:
        self.gpsdata = gpsdata
