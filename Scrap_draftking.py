# Import libraries
import requests
import urllib.request
import time
import json
from selenium import webdriver
import selenium
from bs4 import BeautifulSoup
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains
import csv

#to get the games url
urlmain = 'https://sportsbook.draftkings.com/leagues/basketball/88670846'

print(urlmain)

d = webdriver.Chrome("/local/home/ar245054/AndroidAssests/HotPicks/OLD_STUFF/Scrapper/chromedriver")

d.get(urlmain)

# Connect to the URL
pageSourcemain = d.page_source

# Parse HTML and save to BeautifulSoup object
soupmain = BeautifulSoup(pageSourcemain, "html.parser")


tableurl = soupmain.find_all('a', attrs={"class": "event-cell-link"},href=True)

url = []

count = 0

for a in tableurl:
    url.append('https://sportsbook.draftkings.com'+a['href']+'?category=odds&subcategory=player-props')
    print("Found the URL: ", 'https://sportsbook.draftkings.com'+a['href']+'?category=odds&subcategory=player-props')
    
d.quit()

limit = int(len(url)/2)
for a in range(0,limit):

    print(url[a*2])
    
    d = webdriver.Chrome("/local/home/ar245054/AndroidAssests/HotPicks/OLD_STUFF/Scrapper/chromedriver")
    
    d.get(url[a*2])

    #total_height = int(d.execute_script("return document.body.scrollHeight"))

    #for i in range(1, total_height, 5):
    #    d.execute_script("window.scrollTo(0, {});".format(i))
    #    time.sleep(1)
        
    #input('Done clicking:')
    
    #y = 1000
    #for timer in range(0,5):
    #     d.execute_script("window.scrollTo(0, "+str(y)+")")
    #     y += 1000  
    #     time.sleep(10)
    
    #scroll down
    #d.execute_script("window.scrollTo(0, document.body.scrollHeight);")

    #WebDriverWait(d, 1000)

    # Connect to the URL
    pageSourcemain = d.page_source
    
    # Parse HTML and save to BeautifulSoup object
    soupmain = BeautifulSoup(pageSourcemain, "html.parser")

    row_team = []
    TeamN = []

    #row_teamH.append(['Player','Stat','Val','0.'])
    #row_teamA.append(['Player','Stat','Val','0.'])

    #Get Team Names
    #boxname = soupmain.find_all('div', attrs={"class": "timer"})
    boxname = soupmain.find_all('title')
    #print(len(boxname))
    if len(boxname) >= 1:
        #print(boxname[0].getText())
        Name = boxname[0].getText()
        teama = Name.split(' ')[0]
        teamh = Name.split(' ')[3]
        print(teama)
        print(teamh)
        TeamN.append(teama)
        TeamN.append(teamh)

        
    #Get the bets
    #betbox = soupmain.find('div', attrs={"class": "sportsbook-responsive-card-container"})
    betbox = soupmain.find('section', attrs={"class": "event-page-offers"})
    #print(len(betbox))
    box = betbox.find_all('div', attrs={"class": "sportsbook-event-accordion__wrapper expanded"})
    #print(len(box))

    for b in box:
        boxname = b.find_all('a', attrs={"class": "sportsbook-event-accordion__title active"})
        #print(boxname[0].text)
        #print('Number of boxes : ',len(boxname))
        if len(boxname) == 1:
            player = b.find_all('span', attrs={"class": "sportsbook-row-name"})
            bets = b.find_all('span', attrs={"class": "sportsbook-outcome-cell__line"})
            if boxname[0].text == "Rebounds":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        First = StrPlayer.split(' ')[0]
                        Last = StrPlayer.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Value = bets[2*x].getText()
                        #print(Name)
                        #print(Value)
                        row_team.append([Name,'REB',Value,'0.'])

            if boxname[0].text == "Points":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        First = StrPlayer.split(' ')[0]
                        Last = StrPlayer.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Value = bets[2*x].getText()
                        #print(Name)
                        #print(Value)
                        row_team.append([Name,'PTS',Value,'0.'])

            if boxname[0].text == "Assists":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        First = StrPlayer.split(' ')[0]
                        Last = StrPlayer.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Value = bets[2*x].getText()
                        #print(Name)
                        #print(Value)
                        row_team.append([Name,'AST',Value,'0.'])

            if boxname[0].text == "Threes":
                print("BOX : ", boxname[0].text)
                print("Bets Found : ",len(bets))
                print("Players Found : ",len(player))
                if len(player)*2 == len(bets):
                    for x in range(0,len(player)):
                        #print(bets[2*x].getText())
                        #print(player[x].getText())
                        StrPlayer = player[x].getText()
                        First = StrPlayer.split(' ')[0]
                        Last = StrPlayer.split(' ')[1]
                        Name = First[0]+'. '+Last
                        Value = bets[2*x].getText()
                        #print(Name)
                        #print(Value)
                        row_team.append([Name,'3PM',Value,'0.'])
                                                    
            

    #Generate File Name
    # Create csv and write rows to output file
    fileN = 'bets/draftking_'+teama+'.csv'
    with open(fileN,'w', newline='') as f_output:
        csv_output = csv.writer(f_output)
        csv_output.writerows(row_team)

    fileNH = 'bets/draftking_'+teamh+'.csv'
    with open(fileNH,'w', newline='') as f_outputH:
        csv_outputH = csv.writer(f_outputH)
        csv_outputH.writerows(row_team)
            
    d.quit()
