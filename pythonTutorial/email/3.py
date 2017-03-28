#!/usr/bin/env python

import smtplib
from os.path import basename
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage


def send_mail(send_from, send_to, subject, text, files=None,
              server="smtp.drwholdings.com"):
    assert isinstance(send_to, list)

    msg = MIMEMultipart()
    msg.attach(MIMEText(open('/home/rgirotra/.bashrc').read()))
    msg.attach(MIMEImage(open('/home/rgirotra/Downloads/photo.jpg','rb').read()))
    msg.attach(MIMEText(text))

    print(msg.items())

    smtp = smtplib.SMTP(server)
    smtp.sendmail(send_from, send_to, msg.as_string())
    smtp.close()


send_mail('rgirotra@drwsg.com', ['rgirotra@drwsg.com'], 'SomeSubject', 'SomeText', files=['/home/rgirotra/.bashrc'])
