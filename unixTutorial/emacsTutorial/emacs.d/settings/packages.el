
;; Load yasnippet, enable it in global mode. Define a local directory for your customized snippets.
(when enable-yasnippet
  (require 'yasnippet)
  (yas-global-mode t)  
  (add-to-list 'yas-snippet-dirs "~/.emacs.d/etc/snippets"))

;; Load auto-complete.
(when enable-autocomplete
  (require 'auto-complete)
  ;;(add-to-list 'ac-dictionary-directories "~/.emacs.d/etc/dict")
  (require 'auto-complete-config)
  (ac-config-default))

;; Enable semantic mode - Needed when auto-complete used semantic as a backend for auto-completion.
(when enable-semantic
  (semantic-mode t)
  (global-semantic-idle-scheduler-mode 1))

;; Enable Git front-end
(when enable-magit
  (require 'magit)
  ;;create global key binding M-x magit-status
  (global-set-key (kbd "C-x g") 'magit-status))

;; enable ggtags for C/C++ code browsing.
(when enable-ggtags
   (require 'ggtags)
   (global-set-key (kbd "<f8>") 'ggtags-find-file))

;;enable EDE (Emacs Development Environment)
;;EDE is a minor mode which provides a generic environment for creating, building, and debugging different
;;kinds of projects
(global-ede-mode t)

;;enable elpy for python development

(when enable-elpy
  (elpy-enable)
  ;;fix key binding bugs in elpy
  ;;(define-key yas-minor-mode-map (kbd "C-c k") 'yas-expand)
  ;;(global-set-key (kbd "C-c o") 'iedit-mode)
  )

