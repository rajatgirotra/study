# Lets create a new permission which will allow ReadOnly by default, and write permissions only for the owner.
# so we are using a combination of user and snippet detail to decide on permission

from rest_framework import permissions


class IsOwnerOrReadOnly(permissions.BasePermission):
    def has_object_permission(self, request, view, obj):
        # allow read only for GET, HEAD, OPTIONS which are get urls
        if request.method in permissions.SAFE_METHODS:
            return True
        return obj.owner == request.user
