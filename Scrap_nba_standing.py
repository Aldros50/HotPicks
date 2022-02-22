# Import libraries
import requests
import urllib.request
import time
from bs4 import BeautifulSoup
import csv
import sys
import json

# Set the URL you want to webscrape from
url = 'https://www.espn.com/nba/standings/_/group/league'
print(url)

# Connect to the URL
response = requests.get(url)

# Parse HTML and save to BeautifulSoup object
soup = BeautifulSoup(response.text, "html.parser")

# create and write headers to a list 
rows = []
rows.append(['Name','W','L','PCT','GB','HOME','AWAY','DIV','CONF','PPG','OPP PPG','DIFF','STRK','L10',''])
team = []

#find team names
body = soup.find('body')
abbr = body.find_all('abbr', attrs={'style': 'text-decoration:none'})
td = body.find_all('td', attrs={'class': 'Table__TD'})
tr = body.find_all('tr')
span= body.find_all('span', attrs={'class': 'stat-cell'})
#print(len(tr))

for abr in abbr:
    team.append(abr.getText())
    #print(abr.getText())

#print(len(span))
#for sp in span:
    #print(sp.getText())

count=0
limit = int(len(span)/13)
print(limit)
print(len(span))
for i in range(0,limit):
    W = span[13*count+0].getText()
    L = span[13*count+1].getText()
    PCT = span[13*count+2].getText()
    GB = span[13*count+3].getText()
    Home = span[13*count+4].getText()
    Away = span[13*count+5].getText()
    Div = span[13*count+6].getText()
    Conf = span[13*count+7].getText()
    PPG = span[13*count+8].getText()
    OPPPPG = span[13*count+9].getText()
    DIFF = span[13*count+10].getText()
    STRK = span[13*count+11].getText()
    L10 = span[13*count+12].getText()
       
    rows.append([team[count],W,L,PCT,GB,Home,Away,Div,Conf,PPG,OPPPPG,DIFF,STRK,L10,''])
    count = count+1
    
# Create csv and write rows to output file
fileN = 'NBA_Data/2021_2022/NBA_ranking.csv'
with open(fileN,'w', newline='') as f_output:
    csv_output = csv.writer(f_output)
    csv_output.writerows(rows)

with open('NBA_ranking.html', 'w') as outfile:
    outfile.write('{\"info\":[')
    for i in range(1,31):
        datarow = {'team': rows[i][0], 'W': rows[i][1], 'L': rows[i][2], 'PCT': rows[i][3], 'GB': rows[i][4], 'Home': rows[i][5], 'Away': rows[i][6], 'Div': rows[i][7], 'Conf': rows[i][8], 'PPG': rows[i][9], 'OPPPPG': rows[i][10], 'DIFF': rows[i][11], 'STRK': rows[i][12], 'L10': rows[i][13]}
        outfile.write(json.dumps(datarow, indent=4))
        if i<30:
            outfile.write(',')
    outfile.write(']}')
