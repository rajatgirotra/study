;; load common lisp feature
(require 'cl-lib)

;;add settings directory and packages directory to the load path
(add-to-list 'load-path "~/.emacs.d/settings")
(add-to-list 'load-path "~/.emacs.d/packages")

;;load the correct customizations based on emacs version
(cond
   ((>= emacs-major-version 24) (setq custom-file "~/.emacs.d/settings/custom-24.el"))
   (t (setq custom-file "~/.emacs.d/settings/custom-generic.el")))

(load custom-file)

(defconst enable-ggtags t)

(load "functions.el")
(load "packages.el")
(load "hooks.el")


;;(defun my:ac-c-header-init()
 ;; (require 'auto-complete-c-headers)
;;  (add-to-list 'ac-sources 'ac-source-c-headers)
 ;; (add-to-list 'achead:include-directories '"/puma/prod/gcc/4.9.2-3/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/../../../../include/c++/4.9.2"))

;;(add-hook 'c++-mode-hook 'my:ac-c-header-init)
;;(add-hook 'c-mode-hook 'my:ac-c-header-init)

;;(semantic-mode t)
;;(defun my:add-semantic-to-autocomplete()
 ;; (add-to-list 'ac-sources 'ac-source-semantic))

;;(add-hook 'c-mode-common-hook 'my:add-semantic-to-autocomplete)

;;
;;(defconst enable-ggtags t)

;;global/gtags package settings
;;(when enable-ggtags
 ;;   (require 'ggtags)
  ;;  (global-set-key (kbd "<f8>") 'ggtags-find-file))



;;(add-hook 'c-mode-common-hook
 ;;   (lambda () (when (derived-mode-p 'c-mode 'c++-mode 'java-mode)
  ;;      (global-set-key (kbd "<backtab>") 'toggle-source-header)
   ;;     (ggtags-mode 1))))
