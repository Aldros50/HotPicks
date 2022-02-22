# Import libraries
import requests
import urllib.request
import time
from bs4 import BeautifulSoup
import csv
import sys
import json

# Set the URL you want to webscrape from
url = 'https://www.rotowire.com/basketball/nba-lineups.php'
print(url)

# Connect to the URL
response = requests.get(url)

# Parse HTML and save to BeautifulSoup object
soup = BeautifulSoup(response.text, "html.parser")

team = []

#find team names
game = soup.find_all('div', attrs={'class': 'lineup is-nba'})
#print(len(abbr))

for gg in game:
    team = gg.find_all('div', attrs={'class': 'lineup__abbr'})
    if len(team)==2:
        print(team[0].getText())
        print(team[1].getText())
        # create and write headers to a list 
        rowsH = []
        rowsH.append(['Name','Pos','Pct','Injury',''])
        rowsA = []
        rowsA.append(['Name','Pos','Pct','Injury',''])
        homeline = gg.find_all('ul', attrs={'class': 'lineup__list is-home'})
        for l in homeline:
            li = l.find_all('li')
            #print(len(li))
            for a in li:
                pos = a.find_all('div',attrs={'class': 'lineup__pos'})
                player = a.find_all('a')
                if len(pos)==1:
                    if len(player)==1:
                        #print(pos[0].getText())
                        #print(player[0].getText())
                        #print(len(a['class']))
                        Name = player[0].getText()
                        Pos = pos[0].getText()
                        PctPlay = 0
                        Injury = "NO"
                        if len(a['class'])==2:
                            if a['class'][1]=='is-pct-play-100':
                                PctPlay = 100
                                
                            if a['class'][1]!='is-pct-play-100':
                                print(a['class'][1])
                                                                
                        if len(a['class'])==3:
                            if a['class'][1]=='is-pct-play-100':
                                PctPlay = 100
                            if a['class'][1]=='is-pct-play-75':
                                PctPlay = 75
                            if a['class'][1]=='is-pct-play-50':
                                PctPlay = 50
                            if a['class'][1]=='is-pct-play-25':
                                PctPlay = 25
                            if a['class'][1]=='is-pct-play-0':
                                PctPlay = 0
                            if a['class'][2]=='has-injury-status':
                                Injury = "YES"

                        rowsH.append([Name,Pos,PctPlay,Injury,''])
                        #print(a['class'][1])
                        #print(a['class'][2])
                        #print(a['title'])

        awayline = gg.find_all('ul', attrs={'class': 'lineup__list is-visit'})
        for l in awayline:
            li = l.find_all('li')
            #print(len(li))
            for a in li:
                pos = a.find_all('div',attrs={'class': 'lineup__pos'})
                player = a.find_all('a')
                if len(pos)==1:
                    if len(player)==1:
                        #print(pos[0].getText())
                        #print(player[0].getText())
                        #print(len(a['class']))
                        Name = player[0].getText()
                        Pos = pos[0].getText()
                        PctPlay = 0
                        Injury = "NO"
                        if len(a['class'])==2:
                            if a['class'][1]=='is-pct-play-100':
                                PctPlay = 100
                                
                            if a['class'][1]!='is-pct-play-100':
                                print(a['class'][1])
                                                                
                        if len(a['class'])==3:
                            if a['class'][1]=='is-pct-play-100':
                                PctPlay = 100
                            if a['class'][1]=='is-pct-play-75':
                                PctPlay = 75
                            if a['class'][1]=='is-pct-play-50':
                                PctPlay = 50
                            if a['class'][1]=='is-pct-play-25':
                                PctPlay = 25
                            if a['class'][1]=='is-pct-play-0':
                                PctPlay = 0
                            if a['class'][2]=='has-injury-status':
                                Injury = "YES"
                                
                        rowsA.append([Name,Pos,PctPlay,Injury,''])
                        #print(a['class'][1])
                        #print(a['class'][2])
                        #print(a['title'])

        #TEAM1
        print(team[1].getText())
        print(rowsH)
        print(len(rowsH))
        teamN = team[1].getText()
        if teamN=="SAS":
            teamN="SA"
        if teamN=="GSW":
            teamN="GS"
        if teamN=="NOP":
            teamN="NO"
        if teamN=="UTA":
            teamN="UTAH"
        if teamN=="NYK":
            teamN="NY"
        if teamN=="WAS":
            teamN="WSH"
        fileN = 'NBA_lineups_'+teamN+'.html'
        with open(fileN, 'w') as outfile:
            outfile.write('{\"info\":[')
            for i in range(1,len(rowsH)):
                datarow = {'name': rowsH[i][0], 'pos': rowsH[i][1], 'pct': rowsH[i][2], 'injury': rowsH[i][3]}
                outfile.write(json.dumps(datarow, indent=4))
                if i<len(rowsH)-1:
                    outfile.write(',')
            outfile.write(']}')
    
        #TEAM2
        print(team[0].getText())
        print(rowsA)
        print(len(rowsA))
        teamN = team[0].getText()
        if teamN=="SAS":
            teamN="SA"
        if teamN=="GSW":
            teamN="GS"
        if teamN=="NOP":
            teamN="NO"
        if teamN=="UTA":
            teamN="UTAH"
        if teamN=="NYK":
            teamN="NY"
        if teamN=="WAS":
            teamN="WSH"
        fileN = 'NBA_lineups_'+teamN+'.html'
        with open(fileN, 'w') as outfile:
            outfile.write('{\"info\":[')
            for i in range(1,len(rowsA)):
                datarow = {'name': rowsA[i][0], 'pos': rowsA[i][1], 'pct': rowsA[i][2], 'injury': rowsA[i][3]}
                outfile.write(json.dumps(datarow, indent=4))
                if i<len(rowsA)-1:
                    outfile.write(',')
            outfile.write(']}')
