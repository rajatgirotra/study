#!/usr/bin/env python

import smtplib
from os.path import basename
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.utils import COMMASPACE, formatdate


def send_mail(send_from, send_to, subject, text, files=None,
              server="smtp.drwholdings.com"):
    assert isinstance(send_to, list)

    msg = MIMEMultipart(
        From=send_from,
        To=COMMASPACE.join(send_to),
        Date=formatdate(localtime=True),
        Subject=subject
    )
    msg.attach(MIMEText(text))

    for f in files or []:
        with open(f, "r") as fil:
            msg.attach(MIMEText(fil.read()))
            msg.add_header('Content-Disposition', 'attachment', filename='abc.txt')

    smtp = smtplib.SMTP(server)
    smtp.sendmail(send_from, send_to, msg.as_string())
    smtp.close()


send_mail('rgirotra@drwsg.com', ['rgirotra@drwsg.com'], 'SomeSubject', 'SomeText', files=['/home/rgirotra/.bashrc'])
