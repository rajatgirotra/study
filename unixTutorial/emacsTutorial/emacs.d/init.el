;; load common lisp feature
(require 'cl-lib)

;; add melpa to list of packages
(require 'package)
(package-initialize)

;;add settings directory and packages directory to the load path
(add-to-list 'load-path "~/.emacs.d/settings")
(add-to-list 'load-path "~/.emacs.d/packages")

;;load the correct customizations based on emacs version
(cond
   ((>= emacs-major-version 24) (setq custom-file "~/.emacs.d/settings/custom-24.el"))
   (t (setq custom-file "~/.emacs.d/settings/custom-generic.el")))

(load custom-file)

(defconst enable-ggtags nil "Enable/Disable use of ggtags. ggtags is based on GNU Global which uses exhuberant ctags as a backend")
(defconst enable-yasnippet nil "Enable/Disbale snippet expansion")
(defconst enable-autocomplete nil)
(defconst enable-autocomplete-c-headers nil)
(defconst enable-elpy nil)
(defconst enable-semantic nil)
(defconst enable-magit nil "A front-end to GIT version control system")

(load "functions.el")
(load "packages.el")
(load "hooks.el")
