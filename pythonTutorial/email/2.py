#!/usr/bin/env python

import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage



def send_mail(send_from, send_to, subject, text, files=None,
              server="smtp.drwholdings.com"):
    assert isinstance(send_to, list)

    msg = MIMEText("Sometext")
    msg['From'] = 'mts@drwsg.com'
    msg['Subject'] = subject
    msg['To'] = 'rgirotra@drwsg.com'
    print(msg.items())
    # msg.add_header('Content-Disposition', 'attachement', filename='/home/rgirotra/.bashrc')
    # print(msg.items())

    with smtplib.SMTP(server) as smtp:
        smtp.sendmail(send_from, send_to, msg.as_string())

send_mail('rgirotra@drwsg.com', ['rajatgirotra@yahoo.com'], 'SomeSubject', 'SomeText', files=['/home/rgirotra/.bashrc'])
