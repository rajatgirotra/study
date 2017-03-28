(require 'cl)

(add-to-list 'load-path "~/.emacs.d")
(add-to-list 'load-path "~/.emacs.d/packages/")

(defconst enable-gtags t)

;; global / gtags package settings
(when enable-gtags
  (require 'gtags)
  ;; set gtags-root-dir
  (setq gtags-rootdir (getenv "PUMA_SVN_DIR"))
  ;; key bindings
  (global-set-key (kbd "<f9>") 'gtags-find-tag)
  (global-set-key (kbd "<f10>") 'gtags-find-rtag)
  (global-set-key (kbd "<f11>") 'gtags-find-file)
  (global-set-key (kbd "<f12>") 'gtags-find-tag-from-here))

;;
(defun open-include-file-name ()
  (interactive)
  (let* ((fline (buffer-substring-no-properties (line-beginning-position) (line-end-position)))
         (fname (last (split-string
                       (replace-regexp-in-string "<\\|>\\|\"" "" fline) " "))))
    (print fname)
    (gtags-push-context)
    (gtags-goto-tag (car fname) "Po")))

;;
;; Switch fromm *.<impl> to *.<head> and vice versa
(defun toggle-source-header ()
  (interactive)
  (when (string-match "^\\(.*\\)\\.\\([^.]*\\)$" buffer-file-name)
    (let ((name (match-string 1 buffer-file-name))
          (suffix (match-string 2 buffer-file-name)))
      (cond ((string-match suffix "cpp\\|cc\\|c\\|CPP\\|CC\\|C\\|hcpp\\|icpp")
             (cond ((file-exists-p (concat name ".hpp"))
                    (find-file (concat name ".hpp")))
                   ((file-exists-p (concat name ".hh"))
                    (find-file (concat name ".hh")))
                   ((file-exists-p (concat name ".h"))
                    (find-file (concat name ".h")))
                   ((file-exists-p (concat name ".HPP"))
                    (find-file (concat name ".HPP")))
                   ((file-exists-p (concat name ".HH"))
                    (find-file (concat name ".HH")))
                   ((file-exists-p (concat name ".H"))
                    (find-file (concat name ".H")))))
            ((string-match suffix "hpp\\|hh\\|h\\|HPP\\|HH\\|H")
             (cond ((file-exists-p (concat name ".cpp"))
                    (find-file (concat name ".cpp")))
                   ((file-exists-p (concat name ".hcpp"))
                    (find-file (concat name ".hcpp")))
                   ((file-exists-p (concat name ".cc"))
                    (find-file (concat name ".cc")))
                   ((file-exists-p (concat name ".c"))
                    (find-file (concat name ".c")))
                   ((file-exists-p (concat name ".CPP"))
                    (find-file (concat name ".CPP")))
                   ((file-exists-p (concat name ".CC"))
                    (find-file (concat name ".CC")))
                   ((file-exists-p (concat name ".icpp"))
                    (find-file (concat name ".icpp")))
                   ((file-exists-p (concat name ".C"))
                    (find-file (concat name ".C")))))))))

;; set gtags-mode for c/c++ files
(add-hook 'c++-mode-hook
          (lambda ()
            (gtags-mode 1)
            (global-set-key (kbd "<backtab>") 'toggle-source-header)
            (local-set-key (kbd "<f8>") 'open-include-file-name)))

(shell)
