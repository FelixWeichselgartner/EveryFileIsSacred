import socket, sys, struct, time, json
from OpenWeatherMap_ApiKey import OPENWHEATHER_APIKEY

#pip install beautifulsoup4
from bs4 import BeautifulSoup as bs

HTTP_PORT = 80

def deleteHeader(response):
    pos = response.find('\r\n\r\n')
    data = response[pos:]
    return data

def getWebsite(url, link):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((url, HTTP_PORT))

    request = f'GET {link} HTTP/1.1\r\nHost: {url}\r\nConnection: close\r\nAccept: */*\r\n\r\n'

    s.send(request.encode())
    response = s.recv(4096)
    response = response.decode()
    response = deleteHeader(response)

    soup = bs(response, features="html.parser")
    prettyHTML = soup.prettify()

    print(prettyHTML)

    s.close()

def getClockTime():
    Host = 'pool.ntp.org'
    Port = 123

    data = '\x1b' + 47 * '\0'
    TIME1970 = 2208988800

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto(data.encode('utf-8'), (Host, Port))
    data, address = s.recvfrom(1024)

    #if data:
    #    print(f'From {address}\nData:\n {data}')

    t = struct.unpack( '!12I', data )[10]
    t -= TIME1970

    print(f'Time = {time.ctime(t)}')

    return t

def openWeatherAPI():
    Host = 'api.openweathermap.org'
    request = f'GET /data/2.5/weather?q=München,DE&units=metric&appid={OPENWHEATHER_APIKEY} HTTP/1.1\r\nHost: {Host}\r\nConnection: close\r\nAccept: */*\r\n\r\n'

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect((Host, HTTP_PORT))
    s.send(request.encode())
    response = s.recv(4096)
    response = response.decode()
    data = deleteHeader(response)

    weatherDict = json.loads(data)

    #print(json.dumps(weatherDict, indent=4, sort_keys=True))
    #print()

    T = weatherDict["main"]["temp"]
    p = weatherDict["main"]["pressure"]
    H = weatherDict["main"]["humidity"]

    print(f'temperature: {T} °C')
    print(f'pressure:    {p} hPa')
    print(f'humidity:    {H} %')

    #print(response)

    s.close()

    return T, p, H


if __name__ == "__main__":
    HOST = 'felix-weichselgartner.westeurope.cloudapp.azure.com'
    LINK = '/'
    #LINK += 'static/vendor/bootstrap/css/bootstrap.css'

    getWebsite(HOST, LINK)

    t = getClockTime()

    T, p, H = openWeatherAPI()