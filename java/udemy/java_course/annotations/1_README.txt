Annotations in java are just a way to provide some metadata.
What can be Annotated. We can annotate elements like Class, Methods, Fields, function parameters etc.

All annotation have a
1) Target (i.e. which Element type it applies to)
2) RetentionPolicy (i.e. where does it apply:
      before build time -> RetentionPolicy.SOURCE
      during compilation -> RetentionPolicy.Class
      or at run time -> RetentionPolicy.RUNTIME.
If unsure just use RetentionPolicy.RUNTIME

Some annotation you have seen already.

@Override
@SuppressWarnings("unused") --> yes, annotation can take arguments. These arguments can also have a default.

Creating your own annotation and using it is really trivial. Just create a normal class (Class name should be your annotation name)