Django REST Framework
=====================
Django has an app called rest_framework using which you can create REST API's. To install rest_framework, install the following packages in python first

Required:
---------
pip install djangorestframework

Optional but install anyway
---------------------------
pip install coreapi
pip install django-extensions
pip install Markdown
pip install django-filter
pip install django-crispy-forms
pip install django-guardian
pip install pillow

Add 'rest_framework' to INSTALLED_APPS. rest_framework app can make use of standard django authorization app "django.contrib.auth", you to use it add a dictionary variable REST_FRAMEWORK specifying that we want to use the standard django auth app.

REST_FRAMEWORK = {
    'DEFAULT_PERMISSION_CLASSES': [
        'django.contrib.auth.DjangoModelPermissionsOrAnonReadOnly';
        # Meaning use the standard permissions for known users and allow only read access for unknown users.
    ]
}

To use the RF's (RF is rest_framework) browsable API, you'll want to add login and logout views. For those views to work, add the following to settings.py of your site.

url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework'))
If you don't add the above url, you wont see the login button in the top right corner of the browseable API.

